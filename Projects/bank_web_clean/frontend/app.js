const API_BASE_URL = '';

const state = {
    clients: [],
    pendingConfirm: null,
};

const screens = document.querySelectorAll('.screen');
const menuButtons = document.querySelectorAll('.menu-item[data-screen]');
const navButtons = document.querySelectorAll('[data-screen]');
const clientsTable = document.querySelector('#clientsTable');
const listMessage = document.querySelector('#listMessage');
const totalBalances = document.querySelector('#totalBalances');
const balancesTable = document.querySelector('#balancesTable');
const transactionTotalBalances = document.querySelector('#transactionTotalBalances');
const apiStatus = document.querySelector('#apiStatus');
const systemCard = document.querySelector('#systemCard');
const addDuplicateWarning = document.querySelector('#addDuplicateWarning');
const addAccountInput = document.querySelector('#addClientForm [name="accountNumber"]');
const confirmModal = document.querySelector('#confirmModal');
const modalTitle = document.querySelector('#modalTitle');
const modalText = document.querySelector('#modalText');
const modalConfirm = document.querySelector('#modalConfirm');
const modalCancel = document.querySelector('#modalCancel');
const modalClose = document.querySelector('#modalClose');
const toast = document.querySelector('#toast');

const mainKeyScreens = {
    '1': 'list',
    '2': 'add',
    '3': 'delete',
    '4': 'update',
    '5': 'find',
    '6': 'transactions',
    '7': 'exit',
};

const transactionKeyScreens = {
    '1': 'deposit-action',
    '2': 'withdraw-action',
    '3': 'total-balance-action',
};

function money(value) {
    return Number(value || 0).toLocaleString(undefined, {
        minimumFractionDigits: 2,
        maximumFractionDigits: 2,
    });
}

function escapeHtml(value) {
    return String(value ?? '')
        .replaceAll('&', '&amp;')
        .replaceAll('<', '&lt;')
        .replaceAll('>', '&gt;')
        .replaceAll('"', '&quot;')
        .replaceAll("'", '&#039;');
}

function formDataObject(form) {
    return Object.fromEntries(new FormData(form).entries());
}

function setMessage(selector, message, ok = true) {
    const element = document.querySelector(selector);
    if (!element) return;
    element.textContent = message;
    element.classList.toggle('bad', !ok);
}

function showToast(message, ok = true) {
    toast.textContent = message;
    toast.classList.toggle('bad', !ok);
    toast.classList.remove('hidden');
    window.clearTimeout(showToast.timeout);
    showToast.timeout = window.setTimeout(() => toast.classList.add('hidden'), 3200);
}

function showScreen(name) {
    screens.forEach((screen) => {
        screen.classList.toggle('active', screen.id === `screen-${name}`);
    });

    menuButtons.forEach((button) => {
        const shouldBeActive = button.dataset.screen === name ||
            (['deposit-action', 'withdraw-action', 'total-balance-action'].includes(name) && button.dataset.screen === 'transactions');
        button.classList.toggle('active', shouldBeActive);
    });

    if (name === 'list') {
        loadClients();
    }

    if (name === 'total-balance-action') {
        loadTransactionBalances();
    }
}

function activeScreenName() {
    const active = document.querySelector('.screen.active');
    return active ? active.id.replace('screen-', '') : 'list';
}

function showConfirm({ title, text, confirmText = 'Confirm' }) {
    modalTitle.textContent = title;
    modalText.textContent = text;
    modalConfirm.textContent = confirmText;
    confirmModal.classList.remove('hidden');

    return new Promise((resolve) => {
        state.pendingConfirm = resolve;
    });
}

function closeConfirm(result = false) {
    confirmModal.classList.add('hidden');
    if (state.pendingConfirm) {
        state.pendingConfirm(result);
        state.pendingConfirm = null;
    }
}

modalConfirm.addEventListener('click', () => closeConfirm(true));
modalCancel.addEventListener('click', () => closeConfirm(false));
modalClose.addEventListener('click', () => closeConfirm(false));
confirmModal.addEventListener('click', (event) => {
    if (event.target === confirmModal) closeConfirm(false);
});

navButtons.forEach((button) => {
    button.addEventListener('click', () => showScreen(button.dataset.screen));
});

document.addEventListener('keydown', (event) => {
    const target = event.target;
    const isTyping = target && ['INPUT', 'TEXTAREA', 'SELECT'].includes(target.tagName);

    if (!isTyping) {
        const current = activeScreenName();
        if (current === 'transactions' && transactionKeyScreens[event.key]) {
            showScreen(transactionKeyScreens[event.key]);
            return;
        }

        if (mainKeyScreens[event.key]) {
            showScreen(mainKeyScreens[event.key]);
        }
    }

    if (event.key === 'Escape' && !confirmModal.classList.contains('hidden')) {
        closeConfirm(false);
    }
});

async function apiRequest(path, options = {}) {
    const requestOptions = { ...options };

    if (requestOptions.body) {
        requestOptions.headers = {
            'Content-Type': 'application/json',
            ...(requestOptions.headers || {}),
        };
    }

    const response = await fetch(`${API_BASE_URL}${path}`, requestOptions);
    const text = await response.text();
    const data = text ? JSON.parse(text) : {};

    if (!response.ok) {
        throw new Error(data.error || 'Request failed.');
    }

    return data;
}

async function checkApi() {
    try {
        await apiRequest('/api/health');
        apiStatus.textContent = 'All Systems Operational';
        systemCard.classList.add('online');
    } catch (error) {
        apiStatus.textContent = 'Backend Offline';
        systemCard.classList.remove('online');
    }
}

async function refreshClientsCache() {
    const clientsData = await apiRequest('/api/clients');
    state.clients = clientsData.clients || [];
    return state.clients;
}

function accountExists(accountNumber) {
    return state.clients.some((client) => client.accountNumber === accountNumber.trim());
}

function updateDuplicateWarning() {
    const exists = accountExists(addAccountInput.value);
    addDuplicateWarning.classList.toggle('hidden', !exists);
    addAccountInput.classList.toggle('is-error', exists);
    return exists;
}

async function loadClients() {
    try {
        listMessage.textContent = 'Loading clients...';
        const clients = await refreshClientsCache();
        const balanceData = await apiRequest('/api/balances/total');

        clientsTable.innerHTML = '';

        for (const client of clients) {
            const row = document.createElement('tr');
            row.innerHTML = `
                <td><span class="account-chip">${escapeHtml(client.accountNumber)}</span></td>
                <td>${escapeHtml(client.name)}</td>
                <td>${escapeHtml(client.phone)}</td>
                <td><strong>$${money(client.accountBalance)}</strong></td>
            `;
            clientsTable.appendChild(row);
        }

        totalBalances.textContent = `Total balances: $${money(balanceData.totalBalances)}`;
        listMessage.textContent = clients.length
            ? `Client List (${clients.length}) Client(s).`
            : 'No Clients Available In The System!';
        await checkApi();
        updateDuplicateWarning();
    } catch (error) {
        listMessage.textContent = `Error: ${error.message}`;
        systemCard.classList.remove('online');
        apiStatus.textContent = 'Backend Offline';
    }
}

async function loadTransactionBalances() {
    try {
        const clients = await refreshClientsCache();
        const balanceData = await apiRequest('/api/balances/total');

        balancesTable.innerHTML = '';

        for (const client of clients) {
            const row = document.createElement('tr');
            row.innerHTML = `
                <td><span class="account-chip">${escapeHtml(client.accountNumber)}</span></td>
                <td>${escapeHtml(client.name)}</td>
                <td><strong>$${money(client.accountBalance)}</strong></td>
            `;
            balancesTable.appendChild(row);
        }

        transactionTotalBalances.textContent = `Total balances: $${money(balanceData.totalBalances)}`;
    } catch (error) {
        transactionTotalBalances.textContent = `Error: ${error.message}`;
        showToast(error.message, false);
    }
}

async function ensureClientsLoaded() {
    if (!state.clients.length) {
        try { await refreshClientsCache(); } catch (_) { /* handled by submit request */ }
    }
}

addAccountInput.addEventListener('input', updateDuplicateWarning);
addAccountInput.addEventListener('blur', updateDuplicateWarning);
document.querySelector('#refreshClients').addEventListener('click', loadClients);
document.querySelector('#refreshBalances').addEventListener('click', loadTransactionBalances);

document.querySelector('#addClientForm').addEventListener('submit', async (event) => {
    event.preventDefault();
    const form = event.currentTarget;
    const data = formDataObject(form);

    await ensureClientsLoaded();
    if (updateDuplicateWarning()) {
        setMessage('#addMessage', 'Client with this account number already exists.', false);
        showToast('Account number already exists.', false);
        return;
    }

    const confirmed = await showConfirm({
        title: 'Are you sure you want to add this client?',
        text: 'This action will create a new client with the details shown.',
        confirmText: 'Confirm',
    });

    if (!confirmed) return;

    try {
        await apiRequest('/api/clients', {
            method: 'POST',
            body: JSON.stringify({
                accountNumber: data.accountNumber.trim(),
                pinCode: data.pinCode,
                name: data.name.trim(),
                phone: data.phone.trim(),
                accountBalance: Number(data.accountBalance),
            }),
        });
        form.reset();
        setMessage('#addMessage', 'Client Added Successfully.');
        showToast('Client Added Successfully.');
        await loadClients();
        showScreen('list');
    } catch (error) {
        setMessage('#addMessage', `Error: ${error.message}`, false);
        showToast(error.message, false);
        await refreshClientsCache().catch(() => null);
        updateDuplicateWarning();
    }
});

document.querySelector('#deleteClientForm').addEventListener('submit', async (event) => {
    event.preventDefault();
    const form = event.currentTarget;
    const { accountNumber } = formDataObject(form);

    const confirmed = await showConfirm({
        title: 'Are you sure you want to delete this client?',
        text: `Account ${accountNumber} will be removed from the system.`,
        confirmText: 'Delete',
    });

    if (!confirmed) return;

    try {
        await apiRequest(`/api/clients/${encodeURIComponent(accountNumber.trim())}`, { method: 'DELETE' });
        form.reset();
        setMessage('#deleteMessage', 'Client Deleted Successfully.');
        showToast('Client Deleted Successfully.');
        await loadClients();
    } catch (error) {
        setMessage('#deleteMessage', `Error: ${error.message}`, false);
        showToast(error.message, false);
    }
});

document.querySelector('#updateClientForm').addEventListener('submit', async (event) => {
    event.preventDefault();
    const form = event.currentTarget;
    const data = formDataObject(form);

    const confirmed = await showConfirm({
        title: 'Are you sure you want to update this client?',
        text: `Account ${data.accountNumber} will be overwritten with the new details.`,
        confirmText: 'Update',
    });

    if (!confirmed) return;

    try {
        await apiRequest(`/api/clients/${encodeURIComponent(data.accountNumber.trim())}`, {
            method: 'PUT',
            body: JSON.stringify({
                pinCode: data.pinCode,
                name: data.name.trim(),
                phone: data.phone.trim(),
                accountBalance: Number(data.accountBalance),
            }),
        });
        form.reset();
        setMessage('#updateMessage', 'Client Updated Successfully.');
        showToast('Client Updated Successfully.');
        await loadClients();
    } catch (error) {
        setMessage('#updateMessage', `Error: ${error.message}`, false);
        showToast(error.message, false);
    }
});

document.querySelector('#findClientForm').addEventListener('submit', async (event) => {
    event.preventDefault();
    const form = event.currentTarget;
    const { accountNumber } = formDataObject(form);
    const card = document.querySelector('#foundClient');

    try {
        const data = await apiRequest(`/api/clients/${encodeURIComponent(accountNumber.trim())}`);
        const client = data.client;
        card.classList.remove('hidden');
        card.innerHTML = `
            <h3>The following are the client details:</h3>
            <p><span>Account Number</span><strong>${escapeHtml(client.accountNumber)}</strong></p>
            <p><span>Name</span><strong>${escapeHtml(client.name)}</strong></p>
            <p><span>Phone</span><strong>${escapeHtml(client.phone)}</strong></p>
            <p><span>Account Balance</span><strong>$${money(client.accountBalance)}</strong></p>
        `;
        setMessage('#findMessage', '');
    } catch (error) {
        card.classList.add('hidden');
        setMessage('#findMessage', `Error: ${error.message}`, false);
        showToast(error.message, false);
    }
});

async function transaction(event, action) {
    event.preventDefault();
    const form = event.currentTarget;
    const data = formDataObject(form);
    const titleAction = action === 'deposit' ? 'deposit' : 'withdraw';
    const messageSelector = action === 'deposit' ? '#depositMessage' : '#withdrawMessage';

    const confirmed = await showConfirm({
        title: `Are you sure you want to ${titleAction}?`,
        text: `$${money(data.amount)} will be ${action === 'deposit' ? 'added to' : 'removed from'} account ${data.accountNumber}.`,
        confirmText: action === 'deposit' ? 'Deposit' : 'Withdraw',
    });

    if (!confirmed) return;

    try {
        await apiRequest(`/api/clients/${encodeURIComponent(data.accountNumber.trim())}/${action}`, {
            method: 'POST',
            body: JSON.stringify({ amount: Number(data.amount) }),
        });
        form.reset();
        setMessage(messageSelector, 'Done Successfully.');
        setMessage('#transactionMessage', 'Done Successfully.');
        showToast('Transaction completed successfully.');
        await loadClients();
        showScreen('total-balance-action');
    } catch (error) {
        setMessage(messageSelector, `Error: ${error.message}`, false);
        showToast(error.message, false);
    }
}

document.querySelector('#depositForm').addEventListener('submit', (event) => transaction(event, 'deposit'));
document.querySelector('#withdrawForm').addEventListener('submit', (event) => transaction(event, 'withdraw'));

function startMoneyRain() {
    const canvas = document.querySelector('#moneyRain');
    const context = canvas.getContext('2d');
    const symbols = ['$', '€', '¥', '₿', '01', '++', '{}'];
    let drops = [];

    function resize() {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
        const columns = Math.max(46, Math.floor(canvas.width / 32));
        drops = Array.from({ length: columns }, (_, index) => ({
            x: index * 32,
            y: Math.random() * canvas.height,
            speed: 0.45 + Math.random() * 1.25,
            size: 11 + Math.random() * 7,
            text: symbols[Math.floor(Math.random() * symbols.length)],
        }));
    }

    function draw() {
        context.clearRect(0, 0, canvas.width, canvas.height);

        for (const drop of drops) {
            context.font = `${drop.size}px ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, monospace`;
            context.fillStyle = 'rgba(125, 211, 252, 0.14)';
            context.fillText(drop.text, drop.x, drop.y);
            drop.y += drop.speed;
            if (drop.y > canvas.height + 30) {
                drop.y = -30;
                drop.text = symbols[Math.floor(Math.random() * symbols.length)];
            }
        }

        requestAnimationFrame(draw);
    }

    resize();
    window.addEventListener('resize', resize);
    draw();
}

startMoneyRain();
checkApi();
loadClients();
