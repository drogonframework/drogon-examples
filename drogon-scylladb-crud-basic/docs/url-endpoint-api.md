# url endpoint api

### account related

`/api/availability/email`:

- method:
    - GET
        - headers:
            - n/a

            ---

        - params:
            - q
                - required
                - type: string

            ```
            http://localhost:9090/api/availability/email?q=foo@bar.baz
            ```

            ---

        - expected response:
            ```json
            {
                "data": null,
                "message": "this email already registered",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "this email isn't registered",
                "ok": true
            }
            ```

    ---

`/api/account/data`:

- method:
    - GET
        - headers:
            - Authorization: Bearer {username:password}
                - replace username with your account id with *base64 encoding*
                - replace password to empty
                - from:
                    ```
                    Authorization: Bearer 3baea6b5-374d-4ae1-8dea-35c33b2b2139:
                    ```
                - become:
                    ```
                    Authorization: Bearer M2JhZWE2YjUtMzc0ZC00YWUxLThkZWEtMzVjMzNiMmIyMTM5Og==
                    ```

            ---

        - params:
            - n/a

            ---

        - expected response:
            ```json
            {
                "data":
                {
                    "account":
                    {
                        "created_timestamp": "20240801 11:43:08",
                        "email": "foo@bar.baz",
                        "id": "d488586c-7852-4e9a-96f7-29a9bc6bd8c2"
                    }
                },
                "message": "",
                "ok": true
            }
            ```
            ```json
            {
                "data": null,
                "message": "data doesn't exists",
                "ok": false
            }
            ```

    ---

`/api/account/update`:

- method:
    - PATCH
        - headers:
            - n/a

            ---

        - body:
            - id:
                - required
                - type: string

            - email:
                - required
                - type: string

            ```json
            {
                "id": "4c320880-2cea-4c9c-809d-80c18247eb54",
                "email": "foo@bar.baz"
            }
            ```

            ---

        - expected response:
            ```json
            {
                "data":
                {
                    "id": "d488586c-7852-4e9a-96f7-29a9bc6bd8c2"
                },
                "message": "",
                "ok": true
            }
            ```
            ```json
            {
                "data": null,
                "message": "can't register this email",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "can't request to read data, try again later",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "nothing change",
                "ok": false
            }
            ```

    ---

`/api/account/delete`:

- method:
    - DELETE
        - headers:
            - n/a

            ---

        - body:
            - id:
                - required
                - type: string

            - email:
                - required
                - type: string

            ```json
            {
                "id": "ae0d2025-7d82-40a4-a11f-07f3ab543ccb",
                "email": "foo@bar.baz"
            }
            ```

            ---

        - expected response:
            ```json
            {
                "data": null,
                "message": "account has been removed",
                "ok": true
            }
            ```
            ```json
            {
                "data": null,
                "message": "nothing todo",
                "ok": false
            }
            ```

    ---

`/api/account/register`:

- method:
    - POST
        - headers:
            - n/a

            ---

        - body:
            - email:
                - required
                - type: string

            ```json
            {
                "email": "foo@bar.baz"
            }
            ```

            ---

        - expected response:
            ```json
            {
                "data":
                {
                    "id": "d488586c-7852-4e9a-96f7-29a9bc6bd8c2"
                },
                "message": "",
                "ok": true
            }
            ```
            ```json
            {
                "data": null,
                "message": "can't register this email",
                "ok": false
            }
            ```

    ---

<br>

---

### stash related

`/api/stash/{idAccount}/new`:

- method:
    - POST
        - headers:
            - n/a

            ---

        - compose:
            - idAccount: existing id account

            ```
            http://127.0.0.1:9090/api/stash/4c320880-2cea-4c9c-809d-80c18247eb54/new
            ```

            ---

        - body:
            - stash_name:
                - required
                - type: string

            ```json
            {
                "stash_name": "stash2"
            }
            ```

            ---

        - expected response:
            ```json
            {
                "data": null,
                "message": "stash created",
                "ok": true
            }
            ```
            ```json
            {
                "data": null,
                "message": "can't find id account",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "this stash name already exists for you",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "stash name required at least 4 characters",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "can't create stash for now, try again later",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "error while checking id, try again later",
                "ok": false
            }
            ```

    ---

`/api/stash/{idAccount}/all`:

- method:
    - GET
        - headers:
            - n/a

            ---

        - compose:
            - idAccount: existing id account

            ```
            http://127.0.0.1:9090/api/stash/4c320880-2cea-4c9c-809d-80c18247eb54/all
            ```

            ---

        - body:
            - n/a

            ---

        - expected response:
            ```json
            {
                "data":
                {
                    "stash":
                    [
                        {
                            "created_timestamp": "20240801 14:59:27",
                            "id": "82db987e-51bd-41e1-8cc7-48ea8a78e234",
                            "stas_items":
                            [
                                "item 1",
                                "item 2",
                                "item 3"
                            ],
                            "stash_name": "stash1"
                        },
                        {
                            "created_timestamp": "20240801 16:08:12",
                            "id": "8e262994-0fa4-41c0-8522-76e65ec27193",
                            "stas_items": null,
                            "stash_name": "stash2"
                        }
                    ]
                },
                "message": "",
                "ok": true
            }
            ```
            ```json
            {
                "data": null,
                "message": "can't find id account",
                "ok": false
            }
            ```

    ---

`/api/stash/{idAccount}/{idStash}/add/item`:

- method:
    - PATCH
        - headers:
            - n/a

            ---

        - compose:
            - idAccount: existing id account
            - idStash: existing id stash to related account

            ```
            http://127.0.0.1:9090/api/stash/4c320880-2cea-4c9c-809d-80c18247eb54/82db987e-51bd-41e1-8cc7-48ea8a78e234/add/item
            ```

            ---

        - body:
            - item_name:
                - required
                - type: string

            ```json
            {
                "item_name": "item 1"
            }
            ```

            ---

        - expected response:
            ```json
            {
                "data": null,
                "message": "adding item to this stash",
                "ok": true
            }
            ```
            ```json
            {
                "data": null,
                "message": "you want to put something in this stash, but ...",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "can't find id account",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "this stash proly consumed by black hole",
                "ok": false
            }
            ```

    ---

`/api/stash/{idAccount}/{idStash}/delete`:

- method:
    - DELETE
        - headers:
            - n/a

            ---

        - compose:
            - idAccount: existing id account
            - idStash: existing id stash to related account

            ```
            http://127.0.0.1:9090/api/stash/4c320880-2cea-4c9c-809d-80c18247eb54/8e262994-0fa4-41c0-8522-76e65ec27193/delete
            ```

            ---

        - body:
            - n/a

            ---

        - expected response:
            ```json
            {
                "data": null,
                "message": "stash removed",
                "ok": true
            }
            ```
            ```json
            {
                "data": null,
                "message": "can't find id account",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "this stash proly consumed by black hole",
                "ok": false
            }
            ```

    ---

`/api/stash/{idAccount}/{idStash}/delete/item`:

- method:
    - PATCH
        - headers:
            - n/a

            ---

        - compose:
            - idAccount: existing id account
            - idStash: existing id stash to related account

            ```
            http://127.0.0.1:9090/api/stash/4c320880-2cea-4c9c-809d-80c18247eb54/82db987e-51bd-41e1-8cc7-48ea8a78e234/delete/item
            ```

            ---

        - body:
            - item_name:
                - required
                - type: string

            ```json
            {
                "item_name": "item 1"
            }
            ```

            ---

        - expected response:
            ```json
            {
                "data": null,
                "message": "item 'foo' deleted from this stash",
                "ok": true
            }
            ```
            ```json
            {
                "data": null,
                "message": "you are deleting what?!",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "can't find id account",
                "ok": false
            }
            ```
            ```json
            {
                "data": null,
                "message": "this stash proly consumed by black hole",
                "ok": false
            }
            ```

    ---

<br>

---

###### end of url endpoint api
