# drogon svelte 5 rollup

an example of drogon framework using svelte 5 as the frontend (pre-built)

but why?
1. [drogon](https://drogon.org)
2. [svelte](https://svelte.dev)
3. use your svelte knowledge (it might not all of 'em)
4. fully drogon csp is hard to work with & other reasons with .csp
5. reducing some hardware resource usage on frontend with node based project
6. well, why not

<br>

__*pros:*__
<!-- opinionated -->
- session (and server side) controlled by backend (drogon)
- your javascript, css, & all static files mostly just for the end-user
<!-- what else? -->

<br>

__*cons:*__
<!-- opinionated -->
- a little bit complex for configuration (on c++ side, perhaps)
- no (browser) hot reload during development, reload page manually
<!-- what else? -->

<br>

<br>

## informations

`step to configure, build, & run`:
```sh
# run cmake configure and build
cmake -S . -B build;
cmake --build build;

# build the frontend
npm i;
npm run build::views;

# checkout and run
cd ./.out;
./backend_www;
```

> for frontend development, read `package.json` for more scripts information

<br>

`about directories`
- .config:
    - config project files
    ---
- .vscode:
    - some related to vscode and cmake
    - file ended with .debug suffix is a for debug template, copy and rename to original name without .debug if you need it
    ---
- assets:
    - this dir is your assets to sync
    - the default output dir will be __static__
    - sometimes your web public directory doesn't need to involve with git, you can the output directory inside [assets-sync.js](./assets-sync.js):
        - you also need to check where the [public static asset for the backend](./.config/config.backend_www.json#L20)
    ---
- sources:
    - all the working source code goes here

<br>

`things to consider`
- server side render is from .csp file where the drogon handle it
- you still can use svelte head tag, but the first request render is handled by backend
- see [www_svelte.csp](sources/backend/backend_www/views/www_svelte.csp) to look which value need to be pass from drogon controller, it will be controled by [IDrogonCtlHelper](sources/library/libbackend/src/libbackend/interfaces/idrogon_ctl_helper.hh) most of the time
- you can combine it with drogon filter & drogon middleware
- if you missing something when interact data with svelte component, check which data you pass from backend with `drogon::HttpViewData`

<br>

---

###### end of readme
