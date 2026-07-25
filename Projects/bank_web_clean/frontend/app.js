const API_BASE_URL = '';

// Authentication is proxied through our own Vercel domain. This avoids
// cross-site session-cookie blocking in privacy-focused browsers.
const AUTH_PROXY_URL = '/api/auth';

const authState = { accessToken: null, tokenExpiresAt: 0, organization: null };
const initialAuthQuery = new URLSearchParams(window.location.search);
let passwordResetToken = initialAuthQuery.get('token');
const passwordResetError = initialAuthQuery.get('error');

const authGate = document.querySelector('#authGate');
const applicationShell = document.querySelector('#applicationShell');
const authTabs = document.querySelector('#authTabs');
const signInTab = document.querySelector('#signInTab');
const signUpTab = document.querySelector('#signUpTab');
const signInForm = document.querySelector('#signInForm');
const signUpForm = document.querySelector('#signUpForm');
const recoveryForm = document.querySelector('#recoveryForm');
const resetPasswordForm = document.querySelector('#resetPasswordForm');
const forgotPasswordButton = document.querySelector('#forgotPasswordButton');
const recoveryBackButton = document.querySelector('#recoveryBackButton');
const resetBackButton = document.querySelector('#resetBackButton');
const authMessage = document.querySelector('#authMessage');
const sessionUser = document.querySelector('#sessionUser');
const sessionUserName = document.querySelector('#sessionUserName');
const sessionUserEmail = document.querySelector('#sessionUserEmail');
const sessionAvatar = document.querySelector('#sessionAvatar');
const signOutButton = document.querySelector('#signOutButton');

function setAuthMode(mode) {
    const signingIn = mode === 'signin';
    const signingUp = mode === 'signup';
    const recovering = mode === 'recovery';
    const resetting = mode === 'reset';

    authTabs?.classList.toggle('hidden', recovering || resetting);
    signInTab?.classList.toggle('active', signingIn);
    signUpTab?.classList.toggle('active', signingUp);
    signInForm?.classList.toggle('hidden', !signingIn);
    signUpForm?.classList.toggle('hidden', !signingUp);
    recoveryForm?.classList.toggle('hidden', !recovering);
    resetPasswordForm?.classList.toggle('hidden', !resetting);
    setAuthMessage('');
}

function setAuthMessage(message, ok = true) {
    if (!authMessage) return;
    authMessage.textContent = message;
    authMessage.classList.toggle('bad', !ok);
}

function normalizedEmail(value) {
    return String(value || '').trim().toLowerCase();
}

function authErrorMessage(payload, status) {
    const code = String(payload?.code || payload?.error?.code || '').toUpperCase();
    const rawMessage = String(payload?.message || payload?.error?.message || payload?.error || '').trim();

    const messages = {
        INVALID_EMAIL_OR_PASSWORD: 'Invalid email or password.',
        USER_ALREADY_EXISTS: 'An account already exists for this email. Try signing in or resetting the password.',
        USER_ALREADY_EXISTS_USE_ANOTHER_EMAIL: 'An account already exists for this email. Try signing in or resetting the password.',
        EMAIL_NOT_VERIFIED: 'Please verify your email before signing in.',
        INVALID_TOKEN: 'This password-reset link is invalid or expired. Request a new one.',
        TOKEN_EXPIRED: 'This password-reset link has expired. Request a new one.',
        PASSWORD_TOO_SHORT: 'The password must contain at least 8 characters.',
        PASSWORD_TOO_LONG: 'The password cannot exceed 128 characters.',
        TOO_MANY_REQUESTS: 'Too many attempts. Wait a moment and try again.',
    };

    if (messages[code]) return messages[code];
    if (status === 401) return 'Invalid email or password.';
    if (status === 403) return rawMessage || 'Please verify your email before continuing.';
    if (status === 429) return 'Too many attempts. Wait a moment and try again.';
    if (!rawMessage || rawMessage.toLowerCase() === 'builder error') {
        return `Authentication could not complete the request${status ? ` (${status})` : ''}. Please try again.`;
    }
    return rawMessage;
}

async function authRequest(path, options = {}) {
    const response = await fetch(`${AUTH_PROXY_URL}?path=${encodeURIComponent(path)}`, {
        ...options,
        credentials: 'same-origin',
        headers: {
            ...(options.body ? { 'Content-Type': 'application/json' } : {}),
            ...(options.headers || {}),
        },
    });

    const text = await response.text();
    let payload = null;
    try { payload = text ? JSON.parse(text) : null; } catch { payload = { message: text }; }

    if (!response.ok) {
        throw new Error(authErrorMessage(payload, response.status));
    }
    return payload;
}

function tokenFromPayload(payload) {
    if (typeof payload === 'string') return payload;
    return payload?.token
        || payload?.data?.token
        || payload?.session?.access_token
        || payload?.data?.session?.access_token
        || payload?.access_token
        || null;
}

function tokenExpiration(token) {
    try {
        const encodedPayload = token.split('.')[1];
        const normalized = encodedPayload.replaceAll('-', '+').replaceAll('_', '/');
        const padded = normalized.padEnd(Math.ceil(normalized.length / 4) * 4, '=');
        const payload = JSON.parse(atob(padded));
        return Number(payload.exp || 0) * 1000;
    } catch {
        return 0;
    }
}

function saveAccessToken(token) {
    authState.accessToken = token || null;
    authState.tokenExpiresAt = token ? tokenExpiration(token) : 0;
    return authState.accessToken;
}

async function refreshAccessToken(sessionData = null, force = false) {
    const hasFreshToken = authState.accessToken
        && authState.tokenExpiresAt > Date.now() + 60_000;

    if (!force && hasFreshToken) return authState.accessToken;

    try {
        const tokenData = await authRequest('/token', { method: 'GET' });
        const token = tokenFromPayload(tokenData);
        if (token) return saveAccessToken(token);
    } catch {
        // A newly created session may already contain the token.
    }

    const fallbackToken = tokenFromPayload(sessionData);
    if (fallbackToken) return saveAccessToken(fallbackToken);

    saveAccessToken(null);
    throw new Error('Your secure session is unavailable. Please sign in again.');
}

async function enterAuthenticatedApp(sessionData, organizationName = null) {
    const user = sessionData?.user || sessionData?.data?.user || sessionData?.session?.user;
    if (!user) return false;

    await refreshAccessToken(sessionData, true);

    const onboarding = await apiRequest('/api/onboarding', {
        method: 'POST',
        body: JSON.stringify({
            organizationName,
            displayName: user.name || '',
        }),
    });
    authState.organization = onboarding.organization;

    authGate?.classList.add('hidden');
    applicationShell?.classList.remove('auth-hidden');
    sessionUser?.classList.remove('hidden');
    document.body.classList.remove('landing-mode');
    if (sessionUserName) sessionUserName.textContent = user.name || 'System Bank User';
    if (sessionUserEmail) {
        const orgName = onboarding.organization?.name;
        sessionUserEmail.textContent = orgName ? `${user.email || ''} · ${orgName}` : (user.email || '');
    }
    if (sessionAvatar) sessionAvatar.textContent = String(user.name || user.email || 'U').charAt(0).toUpperCase();
    return true;
}

function openAuthGate() {
    applicationShell?.classList.add('auth-hidden');
    sessionUser?.classList.add('hidden');
    authGate?.classList.remove('hidden');
    document.body.classList.add('landing-mode');
}

function clearAuthQuery() {
    const cleanUrl = `${window.location.pathname}${window.location.hash || ''}`;
    window.history.replaceState({}, document.title, cleanUrl);
    passwordResetToken = null;
}

async function checkAuthSession() {
    if (passwordResetToken) {
        openAuthGate();
        setAuthMode('reset');
        return;
    }

    if (passwordResetError) {
        openAuthGate();
        setAuthMode('recovery');
        setAuthMessage('That reset link is invalid or expired. Request a new one.', false);
        return;
    }

    try {
        const session = await authRequest('/get-session', { method: 'GET' });
        if (!(await enterAuthenticatedApp(session, sessionStorage.getItem('pendingOrganizationName')))) openAuthGate();
        sessionStorage.removeItem('pendingOrganizationName');
    } catch {
        saveAccessToken(null);
        authState.organization = null;
        openAuthGate();
        setAuthMode('signin');
    }
}

signInTab?.addEventListener('click', () => setAuthMode('signin'));
signUpTab?.addEventListener('click', () => setAuthMode('signup'));
forgotPasswordButton?.addEventListener('click', () => {
    const signInEmail = signInForm?.elements?.email?.value;
    if (signInEmail && recoveryForm?.elements?.email) recoveryForm.elements.email.value = signInEmail;
    setAuthMode('recovery');
});
recoveryBackButton?.addEventListener('click', () => setAuthMode('signin'));
resetBackButton?.addEventListener('click', () => {
    clearAuthQuery();
    setAuthMode('signin');
});

document.querySelectorAll('.password-toggle').forEach((button) => {
    button.addEventListener('click', () => {
        const input = button.parentElement?.querySelector('input');
        if (!input) return;
        const showing = input.type === 'text';
        input.type = showing ? 'password' : 'text';
        button.textContent = showing ? 'Show' : 'Hide';
        button.setAttribute('aria-label', showing ? 'Show password' : 'Hide password');
        button.setAttribute('aria-pressed', String(!showing));
    });
});

signInForm?.addEventListener('submit', async (event) => {
    event.preventDefault();
    const submit = signInForm.querySelector('button[type="submit"]');
    const values = Object.fromEntries(new FormData(signInForm).entries());
    submit.disabled = true;
    setAuthMessage('Signing in…');
    try {
        const signInResult = await authRequest('/sign-in/email', {
            method: 'POST',
            body: JSON.stringify({
                email: normalizedEmail(values.email),
                password: values.password,
                rememberMe: values.rememberMe === 'on',
            }),
        });
        const session = signInResult?.user ? signInResult : await authRequest('/get-session', { method: 'GET' });
        if (!(await enterAuthenticatedApp(session))) throw new Error('Session was not created. Please try again.');
        setAuthMessage('');
    } catch (error) {
        setAuthMessage(error.message || 'Unable to sign in.', false);
    } finally {
        submit.disabled = false;
    }
});

signUpForm?.addEventListener('submit', async (event) => {
    event.preventDefault();
    const submit = signUpForm.querySelector('button[type="submit"]');
    const values = Object.fromEntries(new FormData(signUpForm).entries());

    if (values.password !== values.confirmPassword) {
        setAuthMessage('The two passwords do not match.', false);
        signUpForm.elements.confirmPassword.focus();
        return;
    }

    submit.disabled = true;
    setAuthMessage('Creating your account…');
    try {
        const signUpResult = await authRequest('/sign-up/email', {
            method: 'POST',
            body: JSON.stringify({
                name: String(values.name || '').trim(),
                email: normalizedEmail(values.email),
                password: values.password,
                callbackURL: window.location.origin,
            }),
        });

        sessionStorage.setItem('pendingOrganizationName', String(values.organizationName || '').trim());

        try {
            const session = signUpResult?.user
                ? signUpResult
                : await authRequest('/get-session', { method: 'GET' });
            if (await enterAuthenticatedApp(session, values.organizationName)) {
                sessionStorage.removeItem('pendingOrganizationName');
                setAuthMessage('');
                return;
            }
        } catch {
            // Some projects require email verification before a session exists.
        }

        setAuthMode('signin');
        if (signInForm?.elements?.email) signInForm.elements.email.value = normalizedEmail(values.email);
        setAuthMessage('Account created. Check your email if verification is required, then sign in.');
    } catch (error) {
        setAuthMessage(error.message || 'Unable to create account.', false);
    } finally {
        submit.disabled = false;
    }
});

recoveryForm?.addEventListener('submit', async (event) => {
    event.preventDefault();
    const submit = recoveryForm.querySelector('button[type="submit"]');
    const values = Object.fromEntries(new FormData(recoveryForm).entries());
    submit.disabled = true;
    setAuthMessage('Sending reset link…');
    try {
        await authRequest('/request-password-reset', {
            method: 'POST',
            body: JSON.stringify({
                email: normalizedEmail(values.email),
                redirectTo: `${window.location.origin}/`,
            }),
        });
        setAuthMessage('If that email is registered, a password-reset link has been sent.');
    } catch (error) {
        setAuthMessage(error.message || 'Unable to send the reset link.', false);
    } finally {
        submit.disabled = false;
    }
});

resetPasswordForm?.addEventListener('submit', async (event) => {
    event.preventDefault();
    const submit = resetPasswordForm.querySelector('button[type="submit"]');
    const values = Object.fromEntries(new FormData(resetPasswordForm).entries());

    if (!passwordResetToken) {
        setAuthMessage('This password-reset link is missing its security token. Request a new link.', false);
        return;
    }
    if (values.password !== values.confirmPassword) {
        setAuthMessage('The two passwords do not match.', false);
        resetPasswordForm.elements.confirmPassword.focus();
        return;
    }

    submit.disabled = true;
    setAuthMessage('Updating password…');
    try {
        await authRequest('/reset-password', {
            method: 'POST',
            body: JSON.stringify({
                newPassword: values.password,
                token: passwordResetToken,
            }),
        });
        resetPasswordForm.reset();
        clearAuthQuery();
        setAuthMode('signin');
        setAuthMessage('Password updated. You can sign in now.');
    } catch (error) {
        setAuthMessage(error.message || 'Unable to reset the password.', false);
    } finally {
        submit.disabled = false;
    }
});

signOutButton?.addEventListener('click', async () => {
    signOutButton.disabled = true;
    try {
        await authRequest('/sign-out', { method: 'POST', body: '{}' });
    } catch {
        // Always close the local UI even if the remote session has expired.
    } finally {
        signOutButton.disabled = false;
        saveAccessToken(null);
        authState.organization = null;
        openAuthGate();
        setAuthMode('signin');
        setAuthMessage('You have signed out.');
    }
});

const state = {
    clients: [],
    pendingConfirm: null,
    selectedUpdateClient: null,
    addReturnScreen: 'home',
};

const screens = document.querySelectorAll('.screen');
const menuButtons = document.querySelectorAll('.menu-item[data-screen]');
const navButtons = document.querySelectorAll('[data-screen]');
const clientsTable = document.querySelector('#clientsTable');
const listMessage = document.querySelector('#listMessage');
const clientCountText = document.querySelector('#clientCountText');
const listFilterMessage = document.querySelector('#listFilterMessage');
const clientSearch = document.querySelector('#clientSearch');
const balanceFilterMode = document.querySelector('#balanceFilterMode');
const balanceFilterAmount = document.querySelector('#balanceFilterAmount');
const balanceSort = document.querySelector('#balanceSort');
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
const confirmCard = document.querySelector('.confirm-card');
const questionOrb = document.querySelector('.question-orb');
const toast = document.querySelector('#toast');
const mobileMenuBack = document.querySelector('#mobileMenuBack');
const clientListBack = document.querySelector('#clientListBack');
const exitReturnHome = document.querySelector('#exitReturnHome');
const addScreenBack = document.querySelector('#addScreenBack');
const mainMenuBackButtons = document.querySelectorAll('[data-main-menu-back]');
const addScreenBackTitle = addScreenBack?.querySelector('strong');
const addScreenBackDescription = addScreenBack?.querySelector('small');
const refreshClientsButton = document.querySelector('#refreshClients');
const refreshBalancesButton = document.querySelector('#refreshBalances');
const updateLookupForm = document.querySelector('#updateLookupForm');
const updateEditor = document.querySelector('#updateEditor');
const updateClientForm = document.querySelector('#updateClientForm');
const updateClearSelection = document.querySelector('#updateClearSelection');
const updateSelectedName = document.querySelector('#updateSelectedName');
const updateSelectedAccount = document.querySelector('#updateSelectedAccount');

const mainKeyScreens = {
    '1': 'list',
    '2': 'transactions',
    '3': 'exit',
};

const transactionKeyScreens = {
    '1': 'deposit-action',
    '2': 'withdraw-action',
    '3': 'total-balance-action',
};

const themeByScreen = {
    list: 'list',
    add: 'add',
    delete: 'delete',
    update: 'update',
    find: 'find',
    transactions: 'transactions',
    'deposit-action': 'deposit',
    'withdraw-action': 'withdraw',
    'total-balance-action': 'total',
    exit: 'exit',
};

function isMobileLayout() {
    return window.matchMedia('(max-width: 760px)').matches;
}

function setScreenTheme(name) {
    document.body.dataset.theme = themeByScreen[name] || 'home';
}

function openMobileScreen() {
    if (isMobileLayout()) {
        document.body.classList.add('mobile-screen-active');
        window.scrollTo({ top: 0, behavior: 'smooth' });
    }
}

function openMobileMenu() {
    document.body.classList.remove('mobile-screen-active');
    window.scrollTo({ top: 0, behavior: 'smooth' });
}


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

function clientCountTitleHtml(count) {
    if (!count) return 'No Clients Available';
    return `Client List <span class="client-count-glow">${count}</span> Client(s)`;
}

function clientModalCardHtml(client) {
    return `
        <span class="modal-client-card">
            <span class="modal-client-row"><span>Account Number</span><strong>${escapeHtml(client.accountNumber)}</strong></span>
            <span class="modal-client-row"><span>Name</span><strong>${escapeHtml(client.name)}</strong></span>
            <span class="modal-client-row"><span>Phone</span><strong>${escapeHtml(client.phone)}</strong></span>
            <span class="modal-client-row"><span>Balance</span><strong>$${money(client.accountBalance)}</strong></span>
        </span>
    `;
}

function clientUpdatePreviewHtml(client) {
    return `
        <span class="modal-client-card update-preview-card">
            <span class="modal-client-row"><span>Account Number</span><strong>${escapeHtml(client.accountNumber)}</strong></span>
            <span class="modal-client-row"><span>Name</span><strong>${escapeHtml(client.name)}</strong></span>
            <span class="modal-client-row"><span>Phone</span><strong>${escapeHtml(client.phone)}</strong></span>
            <span class="modal-client-row"><span>Balance</span><strong>$${money(client.accountBalance)}</strong></span>
        </span>
    `;
}

function findClientByAccountOrName(query) {
    const value = String(query || '').trim().toLowerCase();
    if (!value) return null;

    const exactAccount = state.clients.find((client) => String(client.accountNumber || '').toLowerCase() === value);
    if (exactAccount) return exactAccount;

    const exactName = state.clients.find((client) => String(client.name || '').toLowerCase() === value);
    if (exactName) return exactName;

    return state.clients.find((client) => String(client.name || '').toLowerCase().includes(value)) || null;
}

function fillUpdateEditor(client) {
    state.selectedUpdateClient = client;

    updateEditor?.classList.remove('hidden');
    if (updateSelectedName) updateSelectedName.textContent = client.name;
    if (updateSelectedAccount) updateSelectedAccount.textContent = client.accountNumber;

    if (updateClientForm) {
        updateClientForm.elements.accountNumber.value = client.accountNumber;
        updateClientForm.elements.pinCode.value = '';
        updateClientForm.elements.name.value = client.name || '';
        updateClientForm.elements.phone.value = client.phone || '';
        updateClientForm.elements.accountBalance.value = Number(client.accountBalance || 0);
    }

    setMessage('#updateMessage', 'Client loaded. You can edit the card now.');
}

function clearUpdateEditor() {
    state.selectedUpdateClient = null;
    updateEditor?.classList.add('hidden');
    updateClientForm?.reset();
    setMessage('#updateMessage', '');
}



function clientNotFoundHtml(accountNumber) {
    const safeAccount = escapeHtml(accountNumber || 'Unknown');

    return `
        <span class="not-found-card">
            <span class="not-found-label">Account Number</span>
            <strong class="not-found-account">${safeAccount}</strong>
            <span class="not-found-message">Client with account number <strong>${safeAccount}</strong> was not found.</span>
        </span>
        <span class="modal-not-found-help">Please check the account number and try again.</span>
    `;
}

async function showClientNotFound(accountNumber) {
    await showConfirm({
        title: 'Client Not Found',
        html: clientNotFoundHtml(accountNumber),
        confirmText: 'OK',
        showCancel: false,
        variant: 'not-found',
        icon: '!',
    });
}

function decorateRefreshButtons() {
    [refreshClientsButton, refreshBalancesButton].forEach((button) => {
        if (!button || button.dataset.decorated === 'true') return;
        button.classList.add('refresh-glow-button');
        button.innerHTML = '<span class="refresh-orb">↻</span><span>Refresh</span>';
        button.dataset.decorated = 'true';
    });
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

function updateAddBackWidget() {
    if (!addScreenBack) return;

    const returnsToClientList = state.addReturnScreen === 'list';
    if (addScreenBackTitle) {
        addScreenBackTitle.textContent = returnsToClientList ? 'Client List' : 'Main Menu';
    }
    if (addScreenBackDescription) {
        addScreenBackDescription.textContent = returnsToClientList
            ? 'Return to the client workspace'
            : 'Return to the home screen';
    }
}

function showScreen(name) {
    const previousScreen = activeScreenName();
    if (name === 'add' && previousScreen !== 'add') {
        state.addReturnScreen = previousScreen === 'list' ? 'list' : 'home';
        updateAddBackWidget();
    }

    document.body.classList.remove('landing-mode');
    document.body.classList.add('workspace-mode');
    setScreenTheme(name);

    screens.forEach((screen) => {
        screen.classList.toggle('active', screen.id === `screen-${name}`);
    });

    menuButtons.forEach((button) => {
        const shouldBeActive = button.dataset.screen === name ||
            (['deposit-action', 'withdraw-action', 'total-balance-action'].includes(name) && button.dataset.screen === 'transactions');
        button.classList.toggle('active', shouldBeActive);
    });

    openMobileScreen();

    if (name === 'list') {
        loadClients();
    }

    if (name === 'total-balance-action') {
        loadTransactionBalances();
    }
}

function activeScreenName() {
    const active = document.querySelector('.screen.active');
    return active ? active.id.replace('screen-', '') : 'home';
}

function showMainMenu() {
    screens.forEach((screen) => screen.classList.remove('active'));
    menuButtons.forEach((button) => button.classList.remove('active'));
    document.body.classList.add('landing-mode');
    document.body.classList.remove('workspace-mode');
    document.body.classList.remove('mobile-screen-active');
    setScreenTheme('home');
    window.scrollTo({ top: 0, behavior: 'smooth' });
}

function showConfirm({
    title,
    text = '',
    html = '',
    confirmText = 'Confirm',
    cancelText = 'Cancel',
    showCancel = true,
    variant = 'default',
    icon = '?',
}) {
    modalTitle.textContent = title;

    if (html) {
        modalText.innerHTML = html;
    } else {
        modalText.textContent = text;
    }

    if (confirmCard) {
        confirmCard.classList.toggle('modal-danger', variant === 'danger');
        confirmCard.classList.toggle('modal-success', variant === 'success');
        confirmCard.classList.toggle('modal-not-found', variant === 'not-found');
        confirmCard.classList.toggle('modal-update', variant === 'update');
    }

    if (questionOrb) {
        questionOrb.textContent = icon;
    }

    if (modalCancel) {
        modalCancel.textContent = cancelText;
        modalCancel.classList.toggle('hidden', !showCancel);
    }

    modalConfirm.textContent = confirmText;
    modalConfirm.classList.toggle('danger-confirm-action', variant === 'danger');
    modalConfirm.classList.toggle('success-confirm-action', variant === 'success');
    modalConfirm.classList.toggle('not-found-confirm-action', variant === 'not-found');
    modalConfirm.classList.toggle('update-confirm-action', variant === 'update');
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

if (mobileMenuBack) {
    mobileMenuBack.addEventListener('click', showMainMenu);
}

clientListBack?.addEventListener('click', showMainMenu);
exitReturnHome?.addEventListener('click', showMainMenu);
mainMenuBackButtons.forEach((button) => button.addEventListener('click', showMainMenu));

addScreenBack?.addEventListener('click', () => {
    if (state.addReturnScreen === 'list') {
        showScreen('list');
        return;
    }

    showMainMenu();
});

window.addEventListener('resize', () => {
    if (!isMobileLayout()) {
        document.body.classList.remove('mobile-screen-active');
    }
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

async function apiRequest(path, options = {}, mayRetry = true) {
    const requestOptions = { ...options };
    const requiresAuthentication = path !== '/api/health';

    if (requiresAuthentication) {
        await refreshAccessToken();
    }

    requestOptions.headers = {
        ...(requestOptions.body ? { 'Content-Type': 'application/json' } : {}),
        ...(authState.accessToken ? { Authorization: `Bearer ${authState.accessToken}` } : {}),
        ...(requestOptions.headers || {}),
    };

    const response = await fetch(`${API_BASE_URL}${path}`, requestOptions);
    const text = await response.text();
    let data = {};

    try {
        data = text ? JSON.parse(text) : {};
    } catch {
        data = { error: text || 'Request failed.' };
    }

    if (!response.ok) {
        if (requiresAuthentication && mayRetry && [401, 403].includes(response.status)) {
            await refreshAccessToken(null, true);
            return apiRequest(path, options, false);
        }

        throw new Error(data.error || data.message || `Request failed (${response.status}).`);
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

function filteredAndSortedClients() {
    const searchText = (clientSearch?.value || '').trim().toLowerCase();
    const mode = balanceFilterMode?.value || 'all';
    const amountText = balanceFilterAmount?.value || '';
    const amount = amountText === '' ? null : Number(amountText);
    const sortMode = balanceSort?.value || 'none';

    let clients = [...state.clients];

    if (searchText) {
        clients = clients.filter((client) => {
            const accountNumber = String(client.accountNumber || '').toLowerCase();
            const name = String(client.name || '').toLowerCase();
            const phone = String(client.phone || '').toLowerCase();
            return accountNumber.includes(searchText) || name.includes(searchText) || phone.includes(searchText);
        });
    }

    if (amount !== null && Number.isFinite(amount) && mode !== 'all') {
        clients = clients.filter((client) => {
            const balance = Number(client.accountBalance || 0);
            return mode === 'less' ? balance < amount : balance > amount;
        });
    }

    if (sortMode === 'low-high') {
        clients.sort((a, b) => Number(a.accountBalance || 0) - Number(b.accountBalance || 0));
    }

    if (sortMode === 'high-low') {
        clients.sort((a, b) => Number(b.accountBalance || 0) - Number(a.accountBalance || 0));
    }

    return clients;
}

function renderClientsTable() {
    const clients = filteredAndSortedClients();
    clientsTable.innerHTML = '';

    if (clientCountText) {
        clientCountText.innerHTML = clientCountTitleHtml(state.clients.length);
    }

    if (listMessage) {
        listMessage.textContent = state.clients.length
            ? 'Search by account, name, or phone. Filter and sort by balance.'
            : 'No Clients Available In The System!';
    }

    if (listFilterMessage) {
        const hasSearch = Boolean((clientSearch?.value || '').trim());
        const hasBalanceFilter = (balanceFilterMode?.value || 'all') !== 'all' && (balanceFilterAmount?.value || '') !== '';
        const hasSort = (balanceSort?.value || 'none') !== 'none';
        const activeTools = hasSearch || hasBalanceFilter || hasSort;
        listFilterMessage.textContent = activeTools
            ? `Showing ${clients.length} of ${state.clients.length} client(s).`
            : 'Showing all clients.';
    }

    if (!clients.length) {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td colspan="5" class="empty-table-cell">No clients match your search or balance filter.</td>
        `;
        clientsTable.appendChild(row);
        return;
    }

    for (const client of clients) {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td><span class="account-chip">${escapeHtml(client.accountNumber)}</span></td>
            <td>${escapeHtml(client.name)}</td>
            <td>${escapeHtml(client.phone)}</td>
            <td><strong>$${money(client.accountBalance)}</strong></td>
            <td class="client-row-actions">
                <button class="row-action row-update-action" type="button" data-client-action="update" data-account="${escapeHtml(client.accountNumber)}" aria-label="Update ${escapeHtml(client.name)}">
                    <span>✎</span>Update
                </button>
                <button class="row-action row-delete-action" type="button" data-client-action="delete" data-account="${escapeHtml(client.accountNumber)}" aria-label="Delete ${escapeHtml(client.name)}">
                    <span>🗑</span>Delete
                </button>
            </td>
        `;
        clientsTable.appendChild(row);
    }
}

async function loadClients() {
    try {
        if (clientCountText) clientCountText.textContent = 'Loading clients...';
        if (listMessage) listMessage.textContent = 'Preparing client list...';
        const clients = await refreshClientsCache();
        const balanceData = await apiRequest('/api/balances/total');

        renderClientsTable();
        totalBalances.textContent = `Total balances: $${money(balanceData.totalBalances)}`;
        await checkApi();
        updateDuplicateWarning();
    } catch (error) {
        if (clientCountText) clientCountText.textContent = 'Client List Error';
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
refreshClientsButton?.addEventListener('click', loadClients);
refreshBalancesButton?.addEventListener('click', loadTransactionBalances);
[clientSearch, balanceFilterMode, balanceFilterAmount, balanceSort].forEach((control) => {
    if (!control) return;
    control.addEventListener('input', renderClientsTable);
    control.addEventListener('change', renderClientsTable);
});

document.querySelector('#addClientForm').addEventListener('submit', async (event) => {
    event.preventDefault();
    const form = event.currentTarget;
    const data = formDataObject(form);

    const newClient = {
        accountNumber: data.accountNumber.trim(),
        pinCode: data.pinCode,
        name: data.name.trim(),
        phone: data.phone.trim(),
        accountBalance: Number(data.accountBalance),
    };

    await ensureClientsLoaded();
    if (updateDuplicateWarning()) {
        setMessage('#addMessage', 'Client with this account number already exists.', false);
        showToast('Account number already exists.', false);
        return;
    }

    const confirmed = await showConfirm({
        title: 'Review this client before adding',
        html: `
            ${clientModalCardHtml(newClient)}
            <span class="modal-success-text">Create this new client in the database?</span>
        `,
        confirmText: 'Add Client',
        variant: 'success',
        icon: '＋',
    });

    if (!confirmed) return;

    try {
        await apiRequest('/api/clients', {
            method: 'POST',
            body: JSON.stringify(newClient),
        });

        await showConfirm({
            title: 'Client Added Successfully',
            html: `
                ${clientModalCardHtml(newClient)}
                <span class="modal-success-text">This client was added to your database.</span>
            `,
            confirmText: 'View Client List',
            showCancel: false,
            variant: 'success',
            icon: '✓',
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

async function deleteClientByAccount(accountNumber, { resetForm = null } = {}) {
    const account = String(accountNumber || '').trim();

    try {
        await ensureClientsLoaded();

        const client = state.clients.find((item) => item.accountNumber === account);

        if (!client) {
            await showClientNotFound(account);
            return false;
        }

        const confirmed = await showConfirm({
            title: 'Review this client before deleting',
            html: `
                ${clientModalCardHtml(client)}
                <span class="modal-danger-text">⚠ Are you sure you want to delete this client?</span>
            `,
            confirmText: 'Delete Client',
            variant: 'danger',
            icon: '🗑',
        });

        if (!confirmed) return false;

        await apiRequest(`/api/clients?accountNumber=${encodeURIComponent(account)}`, {
            method: 'DELETE',
        });

        resetForm?.reset();
        setMessage('#deleteMessage', 'Client Deleted Successfully.');
        showToast('Client Deleted Successfully.');
        await loadClients();
        showScreen('list');
        return true;
    } catch (error) {
        if (String(error.message || '').toLowerCase().includes('not found')) {
            await showClientNotFound(account);
            return false;
        }

        setMessage('#deleteMessage', `Error: ${error.message}`, false);
        showToast(error.message, false);
        return false;
    }
}

clientsTable?.addEventListener('click', async (event) => {
    const actionButton = event.target.closest('[data-client-action]');
    if (!actionButton) return;

    const account = actionButton.dataset.account;
    const client = state.clients.find((item) => item.accountNumber === account);

    if (!client) {
        await showClientNotFound(account);
        return;
    }

    if (actionButton.dataset.clientAction === 'update') {
        showScreen('update');
        updateLookupForm?.reset();
        fillUpdateEditor(client);
        return;
    }

    if (actionButton.dataset.clientAction === 'delete') {
        await deleteClientByAccount(account);
    }
});

document.querySelector('#deleteClientForm').addEventListener('submit', async (event) => {
    event.preventDefault();
    const form = event.currentTarget;
    const { accountNumber } = formDataObject(form);
    await deleteClientByAccount(accountNumber, { resetForm: form });
});

updateLookupForm?.addEventListener('submit', async (event) => {
    event.preventDefault();

    const form = event.currentTarget;
    const { clientQuery } = formDataObject(form);
    const query = clientQuery.trim();

    try {
        await refreshClientsCache();
        const client = findClientByAccountOrName(query);

        if (!client) {
            clearUpdateEditor();
            await showClientNotFound(query);
            return;
        }

        fillUpdateEditor(client);
    } catch (error) {
        setMessage('#updateMessage', `Error: ${error.message}`, false);
        showToast(error.message, false);
    }
});

updateClearSelection?.addEventListener('click', () => {
    clearUpdateEditor();
    updateLookupForm?.reset();
});

updateClientForm?.addEventListener('submit', async (event) => {
    event.preventDefault();

    const form = event.currentTarget;
    const data = formDataObject(form);
    const account = data.accountNumber.trim();

    const updatedClient = {
        accountNumber: account,
        pinCode: data.pinCode,
        name: data.name.trim(),
        phone: data.phone.trim(),
        accountBalance: Number(data.accountBalance),
    };

    const confirmed = await showConfirm({
        title: 'Review this client before updating',
        html: `
            ${clientUpdatePreviewHtml(updatedClient)}
            <span class="modal-update-text">✎ Are you sure you want to update this client?</span>
        `,
        confirmText: 'Update Client',
        variant: 'update',
        icon: '✎',
    });

    if (!confirmed) return;

    try {
        await apiRequest(`/api/clients?accountNumber=${encodeURIComponent(account)}`, {
            method: 'PUT',
            body: JSON.stringify(updatedClient),
        });

        await showConfirm({
            title: 'Client Updated Successfully',
            html: `
                ${clientUpdatePreviewHtml(updatedClient)}
                <span class="modal-update-text">The client information was saved in your database.</span>
            `,
            confirmText: 'View Client List',
            showCancel: false,
            variant: 'update',
            icon: '✓',
        });

        form.reset();
        clearUpdateEditor();
        updateLookupForm?.reset();
        setMessage('#updateMessage', 'Client Updated Successfully.');
        showToast('Client Updated Successfully.');
        await loadClients();
        showScreen('list');
    } catch (error) {
        if (String(error.message || '').toLowerCase().includes('not found')) {
            await showClientNotFound(account);
            return;
        }

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

decorateRefreshButtons();
showMainMenu();
startMoneyRain();
checkApi();
checkAuthSession();
