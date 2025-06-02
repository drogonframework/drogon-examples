import { PROJECT_PUBLIC_DIR } from "./sources/library/libfrontend/src/constants/project";
import { viewBuilder } from "./sources/library/libfrontend/src/functions/viewb";
import { Bundle_t } from "./sources/library/libfrontend/src/types/bundle_type";
import { argv } from "process";

const PRODUCTION = !argv.includes("--watch");

const WWW_HOME_BUNDLE_EN = new Bundle_t(
    "www-home-bundle-en",
    "sources/frontend/src/views/home_en.js",
    "esm",
    PRODUCTION
);
const WWW_HOME_BUNDLE_ID = new Bundle_t(
    "www-home-bundle-id",
    "sources/frontend/src/views/home_id.js",
    "esm",
    PRODUCTION
);

const WWW_SIGNIN_BUNDLE_EN = new Bundle_t(
    "www-signin-bundle-en",
    "sources/frontend/src/views/signin_en.js",
    "esm",
    PRODUCTION
);
const WWW_SIGNIN_BUNDLE_ID = new Bundle_t(
    "www-signin-bundle-id",
    "sources/frontend/src/views/signin_id.js",
    "esm",
    PRODUCTION
);

export default [
// #region www
    //#region en
    {
        // home
        input: [
            WWW_HOME_BUNDLE_EN.source
        ],
        output: {
            name: WWW_HOME_BUNDLE_EN.name,
            file: `${PROJECT_PUBLIC_DIR}/${WWW_HOME_BUNDLE_EN.name}.js`,
            format: WWW_HOME_BUNDLE_EN.format
        },
        plugins: [
            viewBuilder(WWW_HOME_BUNDLE_EN,
                        PROJECT_PUBLIC_DIR,
                        PRODUCTION)
        ]
    },
    {
        // signin
        input: [
            WWW_SIGNIN_BUNDLE_EN.source
        ],
        output: {
            name: WWW_SIGNIN_BUNDLE_EN.name,
            file: `${PROJECT_PUBLIC_DIR}/${WWW_SIGNIN_BUNDLE_EN.name}.js`,
            format: WWW_SIGNIN_BUNDLE_EN.format
        },
        plugins: [
            viewBuilder(WWW_SIGNIN_BUNDLE_EN,
                        PROJECT_PUBLIC_DIR,
                        PRODUCTION)
        ]
    },
    //#endregion
    //#region id
    { // home
        input: [
            WWW_HOME_BUNDLE_ID.source
        ],
        output: {
            name: WWW_HOME_BUNDLE_ID.name,
            file: `${PROJECT_PUBLIC_DIR}/${WWW_HOME_BUNDLE_ID.name}.js`,
            format: WWW_HOME_BUNDLE_ID.format
        },
        plugins: [
            viewBuilder(WWW_HOME_BUNDLE_ID,
                        PROJECT_PUBLIC_DIR,
                        PRODUCTION)
        ]
    },
    {
        // signin
        input: [
            WWW_SIGNIN_BUNDLE_ID.source
        ],
        output: {
            name: WWW_SIGNIN_BUNDLE_ID.name,
            file: `${PROJECT_PUBLIC_DIR}/${WWW_SIGNIN_BUNDLE_ID.name}.js`,
            format: WWW_SIGNIN_BUNDLE_ID.format
        },
        plugins: [
            viewBuilder(WWW_SIGNIN_BUNDLE_ID,
                        PROJECT_PUBLIC_DIR,
                        PRODUCTION)
        ]
    },
    //#endregion
// #endregion
];

// ------------------------------------------------------ //

// TODO: sync "public" or "static" assets
