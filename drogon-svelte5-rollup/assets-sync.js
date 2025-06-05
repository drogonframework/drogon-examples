import chokidar from 'chokidar';
import fs from 'fs-extra';
import path from 'path';
import { fileURLToPath } from 'url';
import { argv } from 'process';
import process from "process";

const __FILENAME = fileURLToPath(import.meta.url);
const __DIRNAME = path.dirname(__FILENAME);

const RUN_ONCE = !argv.includes("--once");

const SOURCE_DIR = path.resolve(__DIRNAME, "assets");
const DEST_DIR = path.resolve(__DIRNAME, "static");
const EXCLUDE_DIRS = [
    "public/u", "public/u/a", "public/u/b", "public/u/i",
    "media/u", "media/u/a", "media/u/b", "media/u/i"
];

/**
 * @param {string} srcPath 
 * @returns void
 */
function syncAddOrUpdate(srcPath) {
    const relativePath = path.relative(SOURCE_DIR, srcPath);
    const destPath = path.join(DEST_DIR, relativePath);

    if (EXCLUDE_DIRS.some((excluded) => relativePath.startsWith(excluded))) {
        return;
    }

    try {
        if (fs.statSync(srcPath).isDirectory()) {
            fs.ensureDirSync(destPath);
        } else {
            fs.copyFileSync(srcPath, destPath);
        }
    } catch (err) {
        if (err instanceof Error) {
            console.error(`[SYNC ERROR] ${err.message}`);
        }
    }
};

/**
 * @param {string} srcPath 
 * @returns void
 */
function syncDelete(srcPath) {
    const relativePath = path.relative(SOURCE_DIR, srcPath);
    const destPath = path.join(DEST_DIR, relativePath);

    if (EXCLUDE_DIRS.some((excluded) => relativePath.startsWith(excluded))) {
        return;
    }

    try {
        if (fs.existsSync(destPath)) {
            fs.removeSync(destPath);
            console.log(`[SYNC] Deleted: ${destPath}`);
        }
    } catch (err) {
        if (err instanceof Error) {
            console.error(`[SYNC ERROR] ${err.message}`);
        }
    }
};

if (!RUN_ONCE) {
    const files = fs.readdirSync(SOURCE_DIR, { recursive: true });

    files.forEach((file) => syncAddOrUpdate(path.join(SOURCE_DIR, file.toString())));
    console.log("[SYNC ONE TIME] Completed.");

    process.exit(0);
}

chokidar.watch(SOURCE_DIR, {
    ignored: EXCLUDE_DIRS.map((dir) => path.join(SOURCE_DIR, dir, "**/*")),
    persistent: true,
    ignoreInitial: false,
}).on("add", (path) => {
    syncAddOrUpdate(path);
    console.log(`[SYNC] Added: ${path}`);
}).on("change", (path) => {
    syncAddOrUpdate(path);
    console.log(`[SYNC] Updated: ${path}`);
}).on("unlink", (path) => {
    syncDelete(path);
}).on("addDir", (path) => {
    syncAddOrUpdate(path);
    console.log(`[SYNC] Directory added: ${path}`);
}).on("unlinkDir", (path) => {
    syncDelete(path);
});
