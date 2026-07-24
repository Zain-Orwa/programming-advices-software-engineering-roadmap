-- System Bank v17
-- Finalize tenant isolation after the authenticated API is installed.
-- Safe to run more than once.

BEGIN;

-- Every authenticated insert now supplies the organization explicitly.
-- Removing the old fallback prevents accidental writes into a shared tenant.
ALTER TABLE clients
    ALTER COLUMN organization_id DROP DEFAULT;

ALTER TABLE clients
    ALTER COLUMN organization_id SET NOT NULL;

-- Preserve tenant-local account numbers and fast organization filtering.
CREATE UNIQUE INDEX IF NOT EXISTS clients_org_account_unique
    ON clients (organization_id, account_number);

CREATE INDEX IF NOT EXISTS clients_organization_id_index
    ON clients (organization_id);

CREATE INDEX IF NOT EXISTS organization_members_user_id_index
    ON organization_members (user_id);

CREATE INDEX IF NOT EXISTS organization_members_org_id_index
    ON organization_members (organization_id);

COMMIT;

-- Verification: organization_id should have no default and no null values.
SELECT
    column_name,
    is_nullable,
    column_default
FROM information_schema.columns
WHERE table_schema = 'public'
  AND table_name = 'clients'
  AND column_name = 'organization_id';

SELECT COUNT(*) AS clients_without_organization
FROM clients
WHERE organization_id IS NULL;
