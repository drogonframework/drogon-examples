# database design

__*INFO*:__

- __KEYSPACE__: `drogon_scylladb_crud_basic`

<br>

__*NOTE:*__
```
each highlighted section (e.g. `account`)
will represent the table name in current KEYSPACE under ## tables
```

<br>

---

## tables

<!-- last updated: 20240801 -->
[V] `account`
```sql
create table if not exists {KEYSPACE}.{TABLE_NAME}
(
    id                  uuid,
    email               text,
    -- could be password_salt text,
    -- could be password_input text,
    created_timestamp   text,

    primary key (id)
);
/*
note:
- id:
    - assume unique
- email:
    - assume unique
*/
```

<br>

<!-- last updated: 20240801 -->
[X] `stash`
```sql
create table if not exists {KEYSPACE}.{TABLE_NAME}
(
    id                  uuid,
    id_account          uuid,
    stash_name          text,
    stash_items         list<text>,
    created_timestamp   text,

    primary key (id)
);
/*
note:
- id_account:
    - related id from account table to lookup
*/
```

<br>

---

###### end of database design
