# .NET 2026 Production Mastery Roadmap

**Primary project:** `FinCore` — a production-style digital banking and wallet platform.  
**Target runtime:** .NET 10 LTS.  
**Purpose:** map every item in the supplied 50-topic tree to a real project location, a production failure to reproduce, a measurable fix, and a dependency-safe learning order.

## First correction: this tree is advanced, but it is not a complete senior roadmap

The 50 topics are excellent for understanding the CLR, performance, ASP.NET Core, EF Core, concurrency, and production diagnosis. They do **not** by themselves make someone senior. A senior engineer must also become strong in testing, security, HTTP/API design, SQL and indexing, observability, resiliency, architecture, code review, deployment, and distributed-system trade-offs. Those subjects should run as a parallel track rather than replacing this tree.

Also, the Arabic phrase translated as a ‘dangerous stage’ means an **advanced or extremely strong level**, not literal danger.

## Why one normal CRUD project is not enough

A banking API covers most of the tree, but low-level memory, plugin loading, source generation, Native AOT, and serious profiling feel artificial unless the solution includes specialized modules. Therefore, use **one solution with several connected projects**, not unrelated tutorial apps.

```text
FinCore.sln
├── src/
│   ├── FinCore.Domain/                 # Money, Account, LedgerEntry, rules
│   ├── FinCore.Application/            # Commands, handlers, validation, interfaces
│   ├── FinCore.Infrastructure/         # EF Core, Dapper, cache, external services
│   ├── FinCore.Api/                    # ASP.NET Core HTTP API
│   ├── FinCore.Worker/                 # Settlement, outbox, notifications
│   ├── FinCore.TransactionIngestion/   # Span, Memory, Channels, parallel processing
│   ├── FinCore.Admin/                  # Small UI client for SynchronizationContext
│   └── FinCore.PluginHost/             # Reflection and AssemblyLoadContext
├── generators/
│   └── FinCore.Generators/             # Roslyn source generators
├── tests/
│   ├── FinCore.UnitTests/
│   ├── FinCore.IntegrationTests/
│   ├── FinCore.ConcurrencyTests/
│   └── FinCore.LoadTests/
└── benchmarks/
    └── FinCore.Benchmarks/              # BenchmarkDotNet
```

## Features that make the concepts real

Customers create accounts, deposit and withdraw money, transfer funds, import transaction files, stream statements, receive notifications, run fraud checks, process settlement jobs, generate reports, and load optional reporting plugins. The system must prevent negative balances, duplicate requests, unauthorized access, race conditions, stale data, and data loss.

## The learning loop for every single topic

1. Explain the mechanism in plain English and draw its execution flow.
2. Build a deliberately naive version inside FinCore.
3. Reproduce a realistic failure under tests or load.
4. Observe evidence: logs, metrics, counters, traces, SQL, allocations, or thread stacks.
5. Fix the root cause and add a regression test.
6. Measure before and after.
7. Write a one-page incident note: symptom → evidence → root cause → fix → prevention.
8. Pass the mastery check: explain when **not** to use the feature.

## Dependency-ordered map of all 50 topics

The original tree groups related subjects, but it is not the safest learning order. The order below preserves every original topic number while moving prerequisites before dependent topics.

### Phase 1 — Runtime, types, and memory

| Step | Original # | Topic                          | Where it lives in FinCore                                                                                                                     | Production failure to reproduce                                                                                                 | Depends on          | Evidence |
| ---- | ---------- | ------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------- | ------------------- | -------- |
| 1    | 1          | CLR & JIT Compilation          | Measure cold vs warm calls to the transfer engine; inspect IL/native code; compare JIT and AOT builds.                                        | Cold-start latency, tiered-compilation surprises, and misleading benchmarks that measure JIT work instead of steady-state work. | C# build/run basics | S1, S2   |
| 2    | 4          | Value Types vs Reference Types | Model `Money` as a small immutable value and accounts/customers as identity-based reference entities; test copying and mutation.              | Accidental copies, shared mutable state, equality bugs, and large structs copied through hot paths.                             | Step 1              | S3       |
| 3    | 6          | Stack vs Heap                  | Trace method frames, local values, object references, closures, recursion, and temporary buffers in transaction processing.                   | Stack overflow, unnecessary heap allocation, and the false rule that every value type is always on the stack.                   | Step 2              | S3, S4   |
| 4    | 5          | Boxing & Unboxing              | Create a high-volume metrics/event path, intentionally box numbers, measure allocations, then replace it with generic or strongly typed code. | Tiny allocations multiplied by millions create GC pressure and latency spikes.                                                  | Steps 2–3           | S5       |
| 5    | 2          | Garbage Collection             | Load-test deposits, transfers, and statement generation while observing allocation rate, heap size, and pause behavior.                       | High allocation rate causes frequent collections; retained references look like leaks even though GC is working correctly.      | Steps 1–4           | S6       |
| 6    | 3          | Generations (0/1/2 & LOH)      | Generate large statement buffers and transaction imports; compare short-lived request objects with long-lived caches.                         | Large buffers enter the LOH; promoted objects increase Gen 2 work and can create long pauses or high memory use.                | Step 5              | S6, S7   |
| 7    | 9          | IDisposable & using            | Manage database connections, streams, readers, responses, timers, and scopes deterministically.                                               | Leaked handles, files, sockets, or DB resources exhaust the process or pool long before managed memory is full.                 | Steps 5–6           | S8       |
| 8    | 10         | Finalizers                     | Wrap a simulated unmanaged handle with the full dispose pattern and prove why explicit disposal is preferred.                                 | Finalizable objects survive longer, add finalizer-queue work, and make cleanup nondeterministic.                                | Step 7              | S8, S9   |
| 9    | 7          | Span<T> & Memory<T>            | Build a zero/low-allocation CSV transaction parser; use `Span<T>` synchronously and `Memory<T>` across async boundaries.                      | Substring and temporary-array allocation makes imports slower and increases GC pressure.                                        | Steps 2–6           | S10      |
| 10   | 8          | ref struct & stackalloc        | Use a bounded temporary parsing buffer and enforce escape-safety rules.                                                                       | Oversized or repeated `stackalloc` can overflow the stack; ref-like values cannot safely escape their lifetime.                 | Step 9              | S10, S11 |

### Phase 2 — Type-system design, callbacks, and queries

| Step | Original # | Topic                       | Where it lives in FinCore                                                                                         | Production failure to reproduce                                                                                                     | Depends on           | Evidence |
| ---- | ---------- | --------------------------- | ----------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------- | -------------------- | -------- |
| 11   | 26         | Generics & Constraints      | Create `Result<T>`, paged results, typed validators, and reusable processing stages with meaningful constraints.  | Runtime casts and weak contracts move errors from compile time into production.                                                     | Phase 1              | S12      |
| 12   | 27         | Covariance & Contravariance | Design read-only providers and handlers so derived transaction types can flow safely through common interfaces.   | Unsafe casts, duplicate adapters, or overly rigid APIs make extension difficult.                                                    | Step 11              | S13      |
| 13   | 28         | Records & Pattern Matching  | Use records for commands/events/DTOs and patterns for deposit, withdrawal, transfer, refund, and fraud decisions. | Using records blindly for EF entities can conflict with identity/reference-equality expectations; giant `if` chains become fragile. | Steps 2 and 11       | S14      |
| 14   | 29         | Nullable Reference Types    | Enable nullable analysis from the start and model optional customer data explicitly.                              | NullReferenceException appears far from the original bad assignment; `!` hides bugs instead of fixing contracts.                    | C# fundamentals      | S15      |
| 15   | 23         | Delegates & Events          | Publish `TransactionPosted`, `TransferFailed`, and `FraudFlagged` domain events.                                  | Long-lived publishers retaining subscribers create memory leaks; duplicate subscriptions send duplicate notifications.              | Steps 11–14          | S16      |
| 16   | 24         | Func, Action & Predicate    | Inject small policies for fee calculation, filtering, retries, and validation.                                    | Captured closures allocate, hide state, and make important business rules difficult to test or observe.                             | Step 15              | S16      |
| 17   | 21         | LINQ & Deferred Execution   | Build statement filters, then intentionally enumerate a deferred query twice before materializing it once.        | Repeated enumeration repeats work or database calls and may produce different results if data changes.                              | Steps 11 and 16      | S17      |
| 18   | 22         | IEnumerable vs IQueryable   | Keep server-side account filtering as `IQueryable` until the query is complete; materialize only at the boundary. | Calling `ToList` too early pulls excessive rows into memory; unsupported expressions fail translation at runtime.                   | Step 17 + SQL basics | S18, S31 |
| 19   | 25         | Expression Trees            | Build a safe dynamic transaction-search specification that EF can translate to SQL.                               | A compiled delegate runs in memory and cannot automatically become SQL; dynamic expressions can produce poor query shapes.          | Steps 16–18          | S19      |

### Phase 3 — Async, threading, and concurrency

| Step | Original # | Topic                     | Where it lives in FinCore                                                                                            | Production failure to reproduce                                                                                                                  | Depends on                    | Evidence |
| ---- | ---------- | ------------------------- | -------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------ | ----------------------------- | -------- |
| 20   | 17         | Threading & Thread Pool   | Run the API under load, introduce blocking work, observe ThreadPool growth/starvation, then remove blocking.         | Requests become slow even with low CPU because worker threads are blocked and new work cannot start promptly.                                    | Phase 1                       | S20      |
| 21   | 11         | Async/Await               | Make database, file, HTTP, and queue operations async end-to-end; inspect the generated state machine.               | Sync-over-async (`.Result`, `.Wait`) can deadlock or starve the pool; fake async wastes threads.                                                 | Step 20                       | S21      |
| 22   | 12         | Task vs ValueTask         | Benchmark a frequently synchronous cache lookup using `Task<T>` and carefully designed `ValueTask<T>`.               | Using `ValueTask` everywhere increases complexity and can be consumed incorrectly; using `Task` in extreme hot paths may allocate unnecessarily. | Step 21 + benchmarking basics | S22      |
| 23   | 13         | SynchronizationContext    | Add a small desktop/admin client and update UI state after awaited operations.                                       | UI freezes, continuation runs on the wrong thread, or blocking the UI thread creates deadlocks.                                                  | Step 21                       | S23      |
| 24   | 14         | ConfigureAwait            | Apply context-capture decisions in a reusable client/library layer, not by superstition throughout application code. | Unnecessary context capture adds overhead in libraries; incorrect use in UI/application code breaks thread-affine assumptions.                   | Step 23                       | S23      |
| 25   | 15         | CancellationToken         | Cancel long statement exports, imports, fraud checks, and graceful application shutdown.                             | Abandoned work continues consuming DB connections, CPU, memory, and external-service capacity after the caller leaves.                           | Step 21                       | S24      |
| 26   | 16         | IAsyncEnumerable          | Stream ledger entries and import results instead of buffering the complete result set.                               | Buffering a huge dataset delays first results and can cause excessive memory use or OOM.                                                         | Steps 21 and 25               | S25      |
| 27   | 18         | lock, Monitor & Semaphore | Reproduce a lost-update/double-spend race; protect in-process state; use `SemaphoreSlim` to bound external calls.    | Race conditions corrupt balances; inconsistent lock order deadlocks; coarse locking destroys throughput.                                         | Step 20                       | S26      |
| 28   | 19         | Channels                  | Create a bounded producer/consumer pipeline for transaction ingestion and notification delivery.                     | An unbounded queue grows until memory is exhausted; missing backpressure lets producers overwhelm consumers.                                     | Steps 21, 25, 27              | S27      |
| 29   | 20         | Parallel & PLINQ          | Parallelize CPU-bound fraud scoring and statement aggregation; compare with sequential work.                         | Parallelizing I/O or tiny tasks increases overhead, pressure, nondeterminism, and contention instead of improving speed.                         | Steps 20 and 27               | S28      |

### Phase 4 — ASP.NET Core application architecture

| Step | Original # | Topic                              | Where it lives in FinCore                                                                                                          | Production failure to reproduce                                                                                                | Depends on       | Evidence |
| ---- | ---------- | ---------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------ | ---------------- | -------- |
| 30   | 30         | Dependency Injection               | Inject repositories, a clock, ID generator, fraud checker, notifier, and fee policy behind explicit interfaces.                    | Hidden service-locator dependencies and hard-coded infrastructure make testing and replacement difficult.                      | Phases 1–3       | S29      |
| 31   | 31         | Service Lifetimes                  | Register DbContext and request services as scoped; prove why a singleton cannot capture scoped mutable state.                      | Disposed objects, cross-request data leakage, non-thread-safe DbContext access, and memory retention.                          | Step 30          | S29      |
| 32   | 35         | Configuration & Options Pattern    | Bind and validate strongly typed options for limits, connection settings, feature flags, and external services.                    | Misspelled or missing settings fail only under traffic; secrets and environment-specific values become scattered through code. | Step 30          | S30      |
| 33   | 32         | Middleware Pipeline                | Add exception handling, correlation IDs, authentication, authorization, timing, and request logging in deliberate order.           | Wrong ordering bypasses security, loses error details, duplicates body reads, or records misleading latency.                   | Steps 30–32      | S31      |
| 34   | 33         | Minimal APIs vs Controllers        | Use Minimal APIs for a small internal/health surface and controllers for the larger versioned banking API; document the trade-off. | Choosing by fashion creates inconsistent conventions, weak discoverability, or needless ceremony.                              | Step 33          | S32      |
| 35   | 34         | Model Binding & Validation         | Validate amount, currency, account ownership, IDs, and request shape at the HTTP boundary.                                         | Invalid or over-posted input reaches the domain, causes incorrect state, or exposes fields clients should not control.         | Step 34          | S33      |
| 36   | 36         | IHostedService & BackgroundService | Run settlement, outbox dispatch, notification retries, and cleanup jobs with scoped dependencies and shutdown cancellation.        | A background exception silently stops processing; singleton workers misuse scoped services; shutdown loses in-flight work.     | Steps 25, 28, 31 | S34      |

### Phase 5 — Persistence and database performance

| Step | Original # | Topic                 | Where it lives in FinCore                                                                                                           | Production failure to reproduce                                                                                          | Depends on            | Evidence |
| ---- | ---------- | --------------------- | ----------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ | --------------------- | -------- |
| 37   | 37         | Entity Framework Core | Persist customers, accounts, ledger entries, idempotency records, and outbox messages with explicit mappings.                       | Convenient ORM use hides query cost, over-fetching, and transaction boundaries.                                          | Phases 2 and 4 + SQL  | S35      |
| 38   | 38         | Change Tracking       | Compare tracked commands with `AsNoTracking` read models; inspect tracked entity counts.                                            | Read-only endpoints retain unnecessary snapshots and identity maps, increasing CPU and memory.                           | Step 37               | S36      |
| 39   | 39         | Migrations            | Create additive, backward-compatible schema changes and a staged deployment plan.                                                   | Application/schema mismatch causes startup failure or downtime; destructive changes lose data or lock large tables.      | Step 37               | S37      |
| 40   | 40         | N+1 Problem           | List accounts with recent transactions, intentionally trigger per-account queries, then fix with projection/eager loading/batching. | A page that looks cheap locally generates hundreds or thousands of DB round trips in production.                         | Steps 17–19 and 37    | S38      |
| 41   | 41         | Connection Pooling    | Load-test DB access, leak a reader/connection in a lab, then diagnose pool exhaustion and timeout behavior.                         | Requests queue or fail while the database is healthy because connections are held too long or pools are fragmented.      | Steps 7, 21, 37       | S39      |
| 42   | 42         | Dapper & Raw SQL      | Implement one measured reporting/hot-path query in EF and Dapper/raw SQL; compare speed, safety, maintenance, and mapping.          | String-built SQL enables injection; hand mappings drift; assuming Dapper is always faster leads to premature complexity. | Steps 18–19 and 37–41 | S40, S41 |

### Phase 6 — Caching and response performance

| Step | Original # | Topic                                | Where it lives in FinCore                                                                                                     | Production failure to reproduce                                                                                                   | Depends on         | Evidence |
| ---- | ---------- | ------------------------------------ | ----------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------- | ------------------ | -------- |
| 43   | 43         | Caching (IMemoryCache & Distributed) | Cache fee rules/reference data and distributed idempotency results; design keys, TTLs, invalidation, and stampede protection. | Stale balances, per-node inconsistency, cache stampedes, unbounded memory, and serialization/versioning failures.                 | Phases 4–5         | S42      |
| 44   | 44         | Output Caching                       | Cache only safe endpoints such as public fee schedules; test variation by route/query/header and authorization rules.         | Caching personalized or authorized responses can leak one user's data to another; incorrect variation serves stale/wrong content. | Steps 33–35 and 43 | S43      |

### Phase 7 — Metaprogramming, plugins, and deployment models

| Step | Original # | Topic                   | Where it lives in FinCore                                                                                                     | Production failure to reproduce                                                                                                          | Depends on                | Evidence |
| ---- | ---------- | ----------------------- | ----------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------- | ------------------------- | -------- |
| 45   | 46         | Reflection & Attributes | Discover attributed transaction handlers and validation/report metadata at startup.                                           | Runtime-only errors, startup scanning cost, hidden coupling, and trimming/AOT incompatibility.                                           | Phases 1–4                | S44, S45 |
| 46   | 45         | Source Generators       | Replace selected reflection-based registration/serialization with generated compile-time code.                                | Opaque generated code and expensive generators slow builds; poor diagnostics make failures difficult to understand.                      | Step 45 + compiler basics | S46, S47 |
| 47   | 47         | AssemblyLoadContext     | Load optional report/fraud plugins with dependency isolation and attempt to unload/reload them.                               | Conflicting dependency versions break plugins; static references, threads, or event subscriptions prevent unloading and leak memory.     | Step 45                   | S48      |
| 48   | 48         | Native AOT              | Publish a small statement/fraud worker as Native AOT; compare startup, memory, size, and compatibility with the normal build. | Reflection or runtime code generation works in JIT mode but fails under trimming/AOT; target-specific publishing complicates deployment. | Steps 45–47               | S49, S50 |

### Phase 8 — Measurement, diagnosis, and production tuning

| Step | Original # | Topic                          | Where it lives in FinCore                                                                                                            | Production failure to reproduce                                                                                                                    | Depends on                                      | Evidence     |
| ---- | ---------- | ------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------- | ------------ |
| 49   | 49         | Benchmarking (BenchmarkDotNet) | Benchmark parser versions, LINQ shapes, EF vs Dapper, Task vs ValueTask, locks vs channels, and JIT vs AOT.                          | Stopwatch tests in Debug mode, missing warmup, dead-code elimination, and noisy machines produce confident but false conclusions.                  | Used lightly earlier; mastered after Steps 1–48 | S51          |
| 50   | 50         | Memory Profiling & GC Tuning   | Run sustained load; collect counters/traces/dumps; find retained caches/subscribers/buffers; fix causes before changing GC settings. | Memory climbs, Gen 2 collections rise, pauses increase, or the process is killed; random `GC.Collect()` calls hide symptoms and reduce throughput. | All previous steps                              | S6, S20, S52 |

## Major production incident labs

| Lab                                         | Failure scenario                                                                                                           | Topics combined                |
| ------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------- | ------------------------------ |
| A. Slow API with normal CPU                 | Block on async work, starve the ThreadPool, hold DB connections, and capture a scoped service incorrectly.                 | 11, 17, 18, 31, 36, 41, 50     |
| B. Memory rises until the process is killed | Use unbounded Channels, retained event subscribers, large statement buffers, and an unbounded cache.                       | 2, 3, 7, 9, 10, 19, 23, 43, 50 |
| C. Database becomes the bottleneck          | Trigger deferred re-execution, early materialization, N+1 queries, unnecessary tracking, and pool exhaustion.              | 21, 22, 25, 37, 38, 40, 41, 42 |
| D. Double-spend race                        | Run simultaneous withdrawals/transfers and observe lost updates; add correct concurrency controls and database guarantees. | 17, 18, 19, 36, 37             |
| E. UI freeze and deadlock                   | Block a UI context on async work, then repair the async flow and cancellation behavior.                                    | 11, 13, 14, 15                 |
| F. Cache leaks private or stale information | Cache an authenticated account response incorrectly, then design safe keys, policies, and invalidation.                    | 32, 34, 43, 44                 |
| G. Plugin cannot unload                     | Retain plugin objects through static fields/events/threads and inspect why the AssemblyLoadContext remains alive.          | 23, 46, 47, 50                 |
| H. JIT build works but Native AOT fails     | Use reflection/dynamic construction that trimming cannot prove, observe warnings, then generate or annotate safe code.     | 1, 45, 46, 47, 48              |
| I. Optimization makes performance worse     | Apply ValueTask, PLINQ, caching, raw SQL, or stackalloc without measurement and prove the regression.                      | 8, 12, 20, 42, 43, 49, 50      |

## Milestones

| Milestone                          | Coverage                                                                                              | Deliverable                                                                         |
| ---------------------------------- | ----------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| M0 — Prerequisites                 | C# syntax, classes/interfaces, exceptions, collections, Git, testing basics, HTTP basics, SQL basics. | A console ledger with unit tests.                                                   |
| M1 — Runtime-aware domain          | Steps 1–19                                                                                            | In-memory banking core, importer, query model, and allocation experiments.          |
| M2 — Concurrent transaction engine | Steps 20–29                                                                                           | Async transfers, cancellation, streaming, bounded queues, race-condition tests.     |
| M3 — Web service                   | Steps 30–36                                                                                           | ASP.NET Core API, DI, validation, middleware, configuration, and workers.           |
| M4 — Durable persistence           | Steps 37–42                                                                                           | EF Core database, migrations, optimized queries, measured Dapper path.              |
| M5 — Scalable reads                | Steps 43–44                                                                                           | Safe distributed caching and output caching.                                        |
| M6 — Extensibility and deployment  | Steps 45–48                                                                                           | Plugin host, generated registrations, and an AOT-published worker.                  |
| M7 — Production proof              | Steps 49–50                                                                                           | Benchmarks, load tests, traces, dumps, incident reports, and before/after evidence. |

## Parallel senior-engineering track that the image omits

| Track                | What to master                                                                                                      |
| -------------------- | ------------------------------------------------------------------------------------------------------------------- |
| Testing              | Unit, integration, contract, concurrency, load, mutation, and failure-injection testing.                            |
| Security             | Authentication, authorization, ownership checks, secret management, OWASP API risks, secure logging, rate limiting. |
| Database engineering | Transactions, isolation levels, optimistic concurrency, indexes, execution plans, locking, backups, recovery.       |
| Observability        | Structured logs, metrics, traces, correlation IDs, dashboards, alerts, SLOs, and postmortems.                       |
| Resilience           | Timeouts, retries with jitter, circuit breakers, bulkheads, idempotency, dead-letter handling.                      |
| Architecture         | Boundaries, coupling/cohesion, modular monoliths, messaging, eventual consistency, outbox/inbox patterns.           |
| Delivery             | Docker, CI/CD, migrations during deployment, health checks, rollback, configuration by environment.                 |
| Engineering practice | Code review, documentation, trade-off writing, debugging unfamiliar code, maintenance and upgrades.                 |

## Definition of mastery for each topic

You have not mastered a topic merely because the code compiles. For each item, you should be able to:

- explain what the runtime/framework is doing;
- identify the symptom it causes in production;
- reproduce the failure intentionally;
- choose the correct diagnostic tool;
- fix it without introducing a different bottleneck;
- prove the improvement with measurements;
- state its limitations and when a simpler option is better.

## Evidence policy for real-world examples

Not every language/runtime concept has a clean public company outage attached to it. For each lesson, use evidence in this order:

1. a verified public postmortem or engineering case study, when one exists;
2. an official .NET diagnostic scenario that reproduces the production failure;
3. an issue from the owning open-source repository with a minimal reproduction;
4. a FinCore load/failure lab that records the same measurable symptom.

Do not invent company incidents merely to make a lesson dramatic.

## Primary sources

- **S1 — .NET 10 LTS support policy (current stable target in August 2026):** https://dotnet.microsoft.com/en-us/platform/support/policy/dotnet-core

- **S2 — .NET runtime overview / managed execution process:** https://learn.microsoft.com/en-us/dotnet/standard/managed-execution-process

- **S3 — C# type system overview:** https://learn.microsoft.com/en-us/dotnet/csharp/fundamentals/types/

- **S4 — Unsafe code and stack/heap guidance:** https://learn.microsoft.com/en-us/dotnet/standard/unsafe-code/best-practices

- **S5 — Boxing and unboxing:** https://learn.microsoft.com/en-us/dotnet/csharp/programming-guide/types/boxing-and-unboxing

- **S6 — Fundamentals of garbage collection:** https://learn.microsoft.com/en-us/dotnet/standard/garbage-collection/fundamentals

- **S7 — Large object heap:** https://learn.microsoft.com/en-us/dotnet/standard/garbage-collection/large-object-heap

- **S8 — Implementing Dispose:** https://learn.microsoft.com/en-us/dotnet/standard/garbage-collection/implementing-dispose

- **S9 — Finalizers:** https://learn.microsoft.com/en-us/dotnet/csharp/programming-guide/classes-and-structs/finalizers

- **S10 — Memory<T> and Span<T> usage guidelines:** https://learn.microsoft.com/en-us/dotnet/standard/memory-and-spans/memory-t-usage-guidelines

- **S11 — stackalloc expression:** https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/operators/stackalloc

- **S12 — Constraints on generic type parameters:** https://learn.microsoft.com/en-us/dotnet/csharp/programming-guide/generics/constraints-on-type-parameters

- **S13 — Covariance and contravariance in generics:** https://learn.microsoft.com/en-us/dotnet/standard/generics/covariance-and-contravariance

- **S14 — C# record types:** https://learn.microsoft.com/en-us/dotnet/csharp/fundamentals/types/records

- **S15 — Nullable reference types:** https://learn.microsoft.com/en-us/dotnet/csharp/fundamentals/null-safety/nullable-reference-types

- **S16 — Delegates overview:** https://learn.microsoft.com/en-us/dotnet/csharp/programming-guide/delegates/

- **S17 — Deferred execution and lazy evaluation in LINQ:** https://learn.microsoft.com/en-us/dotnet/standard/linq/deferred-execution-lazy-evaluation

- **S18 — IQueryable<T> API:** https://learn.microsoft.com/en-us/dotnet/api/system.linq.iqueryable-1

- **S19 — Expression trees:** https://learn.microsoft.com/en-us/dotnet/csharp/advanced-topics/expression-trees/

- **S20 — Debug ThreadPool starvation:** https://learn.microsoft.com/en-us/dotnet/core/diagnostics/debug-threadpool-starvation

- **S21 — How async/await really works:** https://devblogs.microsoft.com/dotnet/how-async-await-really-works/

- **S22 — Understanding ValueTask:** https://devblogs.microsoft.com/dotnet/understanding-the-whys-whats-and-whens-of-valuetask/

- **S23 — ConfigureAwait FAQ and SynchronizationContext:** https://devblogs.microsoft.com/dotnet/configureawait-faq/

- **S24 — Cancellation in managed threads:** https://learn.microsoft.com/en-us/dotnet/standard/threading/cancellation-in-managed-threads

- **S25 — Generate and consume async streams:** https://learn.microsoft.com/en-us/dotnet/csharp/asynchronous-programming/generate-consume-asynchronous-stream

- **S26 — Overview of synchronization primitives:** https://learn.microsoft.com/en-us/dotnet/standard/threading/overview-of-synchronization-primitives

- **S27 — System.Threading.Channels:** https://devblogs.microsoft.com/dotnet/an-introduction-to-system-threading-channels/

- **S28 — Introduction to PLINQ:** https://learn.microsoft.com/en-us/dotnet/standard/parallel-programming/introduction-to-plinq

- **S29 — Dependency injection in ASP.NET Core:** https://learn.microsoft.com/en-us/aspnet/core/fundamentals/dependency-injection?view=aspnetcore-10.0

- **S30 — Options pattern in .NET:** https://learn.microsoft.com/en-us/dotnet/core/extensions/options

- **S31 — ASP.NET Core fundamentals and best practices:** https://learn.microsoft.com/en-us/aspnet/core/fundamentals/best-practices?view=aspnetcore-10.0

- **S32 — Minimal APIs quick reference:** https://learn.microsoft.com/en-us/aspnet/core/fundamentals/minimal-apis?view=aspnetcore-10.0

- **S33 — Model binding in ASP.NET Core:** https://learn.microsoft.com/en-us/aspnet/core/mvc/models/model-binding?view=aspnetcore-10.0

- **S34 — Background tasks with hosted services:** https://learn.microsoft.com/en-us/aspnet/core/fundamentals/host/hosted-services?view=aspnetcore-10.0

- **S35 — Entity Framework Core overview:** https://learn.microsoft.com/en-us/ef/core/

- **S36 — Tracking vs no-tracking queries:** https://learn.microsoft.com/en-us/ef/core/querying/tracking

- **S37 — EF Core migrations overview:** https://learn.microsoft.com/en-us/ef/core/managing-schemas/migrations/

- **S38 — Efficient querying in EF Core:** https://learn.microsoft.com/en-us/ef/core/performance/efficient-querying

- **S39 — SQL Server connection pooling:** https://learn.microsoft.com/en-us/dotnet/framework/data/adonet/sql-server-connection-pooling

- **S40 — SQL queries in EF Core:** https://learn.microsoft.com/en-us/ef/core/querying/sql-queries

- **S41 — Dapper official repository:** https://github.com/DapperLib/Dapper

- **S42 — Distributed caching in ASP.NET Core:** https://learn.microsoft.com/en-us/aspnet/core/performance/caching/distributed?view=aspnetcore-10.0

- **S43 — Output caching middleware:** https://learn.microsoft.com/en-us/aspnet/core/performance/caching/output?view=aspnetcore-10.0

- **S44 — Reflection in .NET:** https://learn.microsoft.com/en-us/dotnet/fundamentals/reflection/overview

- **S45 — Accessing custom attributes:** https://learn.microsoft.com/en-us/dotnet/fundamentals/reflection/accessing-custom-attributes

- **S46 — Roslyn SDK / source generators overview:** https://learn.microsoft.com/en-us/dotnet/csharp/roslyn-sdk/

- **S47 — Source generator cookbook:** https://github.com/dotnet/roslyn/blob/main/docs/features/source-generators.cookbook.md

- **S48 — AssemblyLoadContext:** https://learn.microsoft.com/en-us/dotnet/core/dependency-loading/understanding-assemblyloadcontext

- **S49 — Native AOT deployment:** https://learn.microsoft.com/en-us/dotnet/core/deploying/native-aot/

- **S50 — Native AOT warnings:** https://learn.microsoft.com/en-us/dotnet/core/deploying/native-aot/fixing-warnings

- **S51 — BenchmarkDotNet diagnosers:** https://benchmarkdotnet.org/articles/configs/diagnosers.html

- **S52 — dotnet-counters diagnostic tool:** https://learn.microsoft.com/en-us/dotnet/core/diagnostics/dotnet-counters


## Final direction

Use this document as the **overlay** on top of the instructor's course. The instructor introduces the subject; FinCore turns it into a production problem. When you reach a topic, the lesson should expand that one row into: concept, visual execution flow, wrong implementation, reproduced failure, diagnosis, correct implementation, tests, benchmark, and incident report.
