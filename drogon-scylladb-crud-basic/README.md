# drogon scylladb crud basic

An example of basic create, update, read, and delete with [drogon framework](https://www.drogon.org/) and [scylladb](https://www.scylladb.com/)

<br>

---

## required installed package/library

- [drogon framework](https://github.com/drogonframework/drogon)

- [scylladb cpp driver](https://github.com/scylladb/cpp-driver)

<br>

---

## project short brief

if this is the first time you installed scylladb, consider to:

- set [connection auth mode](./configs/json/backend.api.json#L15) to 1
- set [connection auth mode](./configs/json/backend.api.json#L15) to 2, if you already set username and password for database connection, by default it will using `cassandra` as username & `cassandra` as password
- the rest of connection auth mode hasn't been tested

<br>

---

## confirmed & tested informations

`operating system:`
- __*Debian 12 - WSL*__

<br>

`scylladb:`
- __*engine version:*__
    - *6.0.x ( Debian 12 WSL )*
- __*engine strategy:*__
    - *LocalStrategy ( 6.0.x )*

<br>

---

## extra information

- reserved ports:
    - __9090__

    <br>

- documentations:
    - [database design](./docs/database-design.md)
    - [url endpoint api](./docs/url-endpoint-api.md)
    - [thunder client collection for this example](./thunder_client-collection-drogon-_scylladb_crud_basic.json)

    <br>

    - [scylladb collection types](https://opensource.docs.scylladb.com/stable/cql/types.html#collections)
    - [scylladb custom defined types](https://opensource.docs.scylladb.com/stable/cql/types.html#user-defined-types)
    - [scylladb enable/disable authentication](https://opensource.docs.scylladb.com/stable/operating-scylla/security/runtime-authentication.html)

<br>

---

###### end of drogon scylladb crud basic
