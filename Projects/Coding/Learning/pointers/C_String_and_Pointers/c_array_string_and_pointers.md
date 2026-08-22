# 🧩 **C STRING & POINTER BOOTCAMP**

### “From `char` arrays to string arrays — mastering memory one byte at a time.”

---

## 🧱 **Lesson 00 — Understanding What a String Is**

### 🧠 Concept

A C string is **an array of characters** ending with a special terminator:
`'\0'` (NUL character).

```c
char word[] = "Hi";       // ['H', 'i', '\0']
char *msg = "Hello";      // pointer to string literal
```

> ⚠️ A **string literal** (`"Hello"`) is read-only.
> You can modify a `char[]`, but **never modify** a literal.

---

### ✅ Example

```c
#include <stdio.h>

int main(void)
{
	char s[] = "cat";
	printf("String: %s\n", s);
	printf("Length: %zu\n", strlen(s));   // 3
	printf("Size:   %zu\n", sizeof(s));   // 4 (includes '\0')
}
```

---

### 🎯 Exercise 00

1. Declare a mutable string: `char str[] = "dog";`
2. Replace the first letter with `'f'`.
3. Print the result.

**Expected output**

```
fog
```

---

## 🧱 **Lesson 01 — Pointer vs Array Access**

### 🧠 Concept

`arr[i]` is equivalent to `*(arr + i)`.
Both read the same byte in memory.

```c
char s[] = "code";
printf("%c\n", s[2]);      // d
printf("%c\n", *(s + 2));  // d
```

---

### ✅ Example

```c
#include <stdio.h>

int main(void)
{
	char str[] = "test";
	for (int i = 0; str[i] != '\0'; i++)
		printf("%c ", *(str + i));
}
```

**Output**

```
t e s t
```

---

### 🎯 Exercise 01

Write a function `ft_strlen` that counts characters before `'\0'`.

```c
size_t	ft_strlen(const char *s)
{
	size_t	i = 0;
	while (s[i])
		i++;
	return (i);
}
```

**Test**

```c
printf("%zu\n", ft_strlen("School 42")); // 9
```

---

## 🧱 **Lesson 02 — Array of Strings**

### 🧠 Concept

An “array of strings” = **array of pointers**, each pointing to the first character of a string.

```c
char *titles[] = {
	"Hamlet",
	"Odyssey",
	"Moby-Dick"
};
```

`titles[i]` → pointer to the i-th string
`*titles[i]` → first character of that string

---

### ✅ Example

```c
#include <stdio.h>

int main(void)
{
	char *titles[] = {"Hamlet", "Odyssey", "Moby-Dick"};
	for (int i = 0; i < 3; i++)
		printf("Title[%d]: %s\n", i, titles[i]);
}
```

**Output**

```
Title[0]: Hamlet
Title[1]: Odyssey
Title[2]: Moby-Dick
```

---

### 🎯 Exercise 02

Print only the **first character** of each title.

**Expected**

```
H
O
M
```

Then modify your loop to print the **whole titles**.
Explain the difference between `*titles[i]` and `titles[i]`.

---

## 🧱 **Lesson 03 — Counting Elements Correctly**

### 🧠 Concept

`strlen()` counts characters in a single string.
To count how many **strings** exist in an array, use `sizeof`.

```c
int count = sizeof(titles) / sizeof(titles[0]);
```

---

### ✅ Example

```c
char *titles[] = {"A", "BB", "CCC"};
printf("Strings: %lu\n", sizeof(titles) / sizeof(*titles)); // 3
printf("Length of [1]: %lu\n", strlen(titles[1]));          // 2
```

---

### 🎯 Exercise 03

1. Declare an array of 5 book titles.
2. Print:

   * the number of titles
   * the length of each title

**Expected example**

```
Titles: 5
Book[0]: 12 characters
Book[1]: 9 characters
...
```

---

## 🧱 **Lesson 04 — 2D Character Arrays**

### 🧠 Concept

Alternative representation:
Instead of an array of pointers → one **block of characters** with fixed row length.

```c
char names[3][20] = {"Tom", "Jerry", "Spike"};
```

Each “string” has a fixed maximum size (20).

---

### ✅ Example

```c
#include <stdio.h>

int main(void)
{
	char names[3][20] = {"Tom", "Jerry", "Spike"};

	for (int i = 0; i < 3; i++)
		printf("%s\n", names[i]);
}
```

---

### 🎯 Exercise 04

Create `char animals[4][15]` and fill it with:

```
Dog
Cat
Horse
Elephant
```

Print all animals.
Then print the **ASCII value** of the last character of each word.

---

## 🧱 **Lesson 05 — Iterating Characters in Strings**

### 🧠 Concept

To loop inside a string, use a pointer that moves one character at a time.

```c
for (char *p = titles[i]; *p; p++)
	printf("%c", *p);
```

---

### ✅ Example

```c
char *title = "Odyssey";
for (char *p = title; *p; p++)
	printf("%c ", *p);
```

**Output**

```
O d y s s e y
```

---

### 🎯 Exercise 05

Write a loop that prints **each title letter by letter**, one per line:

```
Title[0]:
H
a
m
l
e
t
```

---

## 🧱 **Lesson 06 — Safe String Copying**

### 🧠 Concept

Always leave space for the `'\0'`.
Use `snprintf` or `strncpy` safely.

---

### ✅ Example

```c
char dst[20];
snprintf(dst, sizeof(dst), "%s", "Hello");
printf("%s\n", dst);
```

---

### 🎯 Exercise 06

Write your own safe copy:

```c
void	ft_strcpy(char *dst, const char *src, size_t size)
{
	size_t	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
```

Test it with:

```c
char buf[6];
ft_strcpy(buf, "abcdef", sizeof(buf));
printf("%s\n", buf);
```

Expected → `abcde`

---

## 🧱 **Lesson 07 — Modifying Mutable Strings**

### 🧠 Concept

You can change characters only if the string is stored in a `char[]`.

---

### ✅ Example

```c
char word[] = "hello";
word[0] = 'H';
printf("%s\n", word);   // Hello
```

---

### 🎯 Exercise 07

Write a function `ft_to_upper` that converts all lowercase letters to uppercase **in place**.

Test:

```c
char str[] = "aBc42";
ft_to_upper(str);
printf("%s\n", str);
```

Expected → `ABC42`

---

## 🧱 **Lesson 08 — Real Practice: Title Library**

### 🧠 Task

Build a small program that:

1. Stores 7 titles in `char *titles[]`.
2. Prints:

   * Total titles count
   * Each title + its length
   * The first letter of each
   * The total number of characters across all titles

---

### ✅ Example Output

```
Total: 7 titles

[0] Hamlet (6)
[1] Odyssey (7)
[2] Moby-Dick (9)
[3] Don Quixote (11)
[4] A Tale of Two Cities (21)
[5] Wuthering Heights (17)
[6] Gulliver's Travels (18)

Total characters: 89
```

---

## 🧱 **Lesson 09 — Common Pitfalls**

| Mistake                          | Problem                                   | Fix                                  |
| :------------------------------- | :---------------------------------------- | :----------------------------------- |
| `strlen(titles)`                 | ❌ titles is array of pointers, not string | use `sizeof(titles)/sizeof(*titles)` |
| `char *s = "hi"; s[0] = 'H';`    | ❌ modifying literal                       | use `char s[] = "hi";`               |
| forget `'\0'`                    | string not terminated                     | always allocate +1                   |
| `%d` for size_t                  | undefined                                 | use `%zu`                            |
| `strcpy(dst, src)` without bound | may overflow                              | use `snprintf` or custom safe copy   |

---

## 🧱 **Lesson 10 — Final Project**

### 🎯 Task

Implement a **tiny string database**.

**Requirements**

* Store up to 10 strings.
* Each string ≤ 31 chars.
* Add, print, and search (exact match).
* Exit when user types `"exit"`.

**Prototype**

```c
int main(void)
{
	char db[10][32];
	int	count = 0;

	while (count < 10)
	{
		printf("Add title (or exit): ");
		fgets(db[count], sizeof(db[count]), stdin);
		db[count][strcspn(db[count], "\n")] = '\0';
		if (strcmp(db[count], "exit") == 0)
			break;
		count++;
	}
	printf("\nStored titles:\n");
	for (int i = 0; i < count; i++)
		printf("[%d] %s\n", i, db[i]);
}
```

---

# 🧠 **Final Notes**

| Concept                        | Summary                        |
| :----------------------------- | :----------------------------- |
| String                         | char array ending with '\0'    |
| `char *`                       | pointer to first character     |
| Array of strings               | array of `char *`              |
| `strlen`                       | counts characters until `'\0'` |
| `sizeof(array)/sizeof(*array)` | number of elements             |
| Mutable vs literal             | only `char[]` is writable      |
| Safe copy                      | leave space for terminator     |
| Print safely                   | `%s` for string, `%c` for char |

---

