import { Bundle_t } from "../types/bundle_type";
import { deleteFiles } from "./copdel";
import alias from "@rollup/plugin-alias";
import scss from "rollup-plugin-scss";
import svelte from "rollup-plugin-svelte";
import { sveltePreprocess } from "svelte-preprocess";
import terser from "@rollup/plugin-terser";
import resolve from "@rollup/plugin-node-resolve";
import commonjs from "@rollup/plugin-commonjs";
import json from "@rollup/plugin-json";
import progress from "rollup-plugin-progress";
import path from "path";

const PROJECT_ROOT_DIR = __dirname; // this will point tp project root dir, "drogon-svelte5-rollup"

/**
 * @type {string[]}
 */
const DEFAULT_EXTENSIONS = [
    ".js",
    ".css",
    ".scss",
    ".svelte",
    ".svelte.js",
];

/**
 * @param {Bundle_t} _bundle 
 * @param {string} _publicStaticDir public static location
 * @param {boolean} _production mosly for terser
 * @param {number} _svelteMajorVersion default 5
 */
export async function viewBuilder(_bundle, _publicStaticDir, _production, _svelteMajorVersion = 5) {
    return [
        await deleteFiles(_publicStaticDir, [
            `${_bundle}.js`,
            `${_bundle}.js.map`,
            `${_bundle}.css`
        ], true),
        alias({
            entries: [
                {
                    find: "@libfrontend",
                    replacement: path.resolve(PROJECT_ROOT_DIR, "sources/library/libfrontend/src/")
                },
            ]
        }),
        scss({
            name: `${_bundle.name}.css`,
            fileName: `${_bundle.name}.css`
        }),
        svelte({
            preprocess: [ sveltePreprocess() ],
            compilerOptions: {
                dev: !_production,
                name: `${_bundle}`.toString(),
                generate: "client",
                immutable: false,
                customElement: false,
                discloseVersion: true,
                runes: (_svelteMajorVersion > 4) ? true : false,
                compatibility: {
                    componentApi: (_svelteMajorVersion <= 4) ? 4 : 5
                }
            }
        }),
        _production && terser(),
        resolve({
            browser: true,
            extensions: DEFAULT_EXTENSIONS,
            // exportConditions: [ "svelte", "svelte.js" ],
            preferBuiltins: true
        }),
        commonjs({
            extensions: DEFAULT_EXTENSIONS
        }),
        json(),
        progress({
            clearLine: _production
        }),
    ]
}
