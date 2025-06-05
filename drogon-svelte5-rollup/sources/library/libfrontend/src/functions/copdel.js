import fs from "fs";
import path from "path";

/**
 * @note USAGE:
 * @note await deleteFile(__dirname, 'example.txt');
 * 
 * @param {*} directory 
 * @param {*} filename 
 */
export async function deleteFile(directory, filename) {
    const FILE_PATH = path.join(directory, filename);
    try {
        await fs.promises.unlink(FILE_PATH);
    } catch (error) {
        // @ts-ignore
        console.error(`ERROR deleting file: ${error.message}`);
    }
}

/**
 * @note USAGE:
 * @note await deleteFiles(__dirname, ['file1.txt', 'file2.txt']);
 * 
 * @param {*} directory 
 * @param {*} filenames 
 */
export async function deleteFiles(directory, filenames, force = true) {
    try {
        // @ts-ignore
        await Promise.all(filenames.map(filename => {
            const FILE_PATH = path.join(directory, filename);
            return fs.promises.unlink(FILE_PATH);
        }));
    } catch (error) {
        if (!force) {
            // @ts-ignore
            console.error(`ERROR deleting files: ${error.message}`);
        }
    }
}

/**
 * @note USAGE:
 * @note await copyFile(__dirname, 'source.txt', __dirname, 'destination.txt');
 * 
 * @param {*} srcDir 
 * @param {*} srcFilename 
 * @param {*} destDir 
 * @param {*} destFilename 
 */
export async function copyFile(srcDir, srcFilename, destDir, destFilename) {
    const SOURCE_PATH = path.join(srcDir, srcFilename);
    const DESTINATION_PATH = path.join(destDir, destFilename);
    try {
        await fs.promises.copyFile(SOURCE_PATH, DESTINATION_PATH);
    } catch (error) {
        // @ts-ignore
        console.error(`ERROR copying file: ${error.message}`);
    }
}

/**
 * @note USAGE:
 * @note await copyFiles(__dirname, [ * { srcFilename: 'source1.txt', destFilename: 'destination1.txt' }, * { srcFilename: 'source2.txt', destFilename: 'destination2.txt' } * ], __dirname);
 * 
 * @param {*} srcDir 
 * @param {*} files 
 * @param {*} destDir 
 */
export async function copyFiles(srcDir, files, destDir) {
    try {
        // @ts-ignore
        await Promise.all(files.map(({ srcFilename, destFilename }) =>
        {
            const SOURCE_PATH = path.join(srcDir, srcFilename);
            const DESTINATION_PATH = path.join(destDir, destFilename);
            return fs.promises.copyFile(SOURCE_PATH, DESTINATION_PATH);
        }));
    } catch (error) {
        // @ts-ignore
        console.error(`ERROR copying files: ${error.message}`);
    }
}

/**
 * @note USSAGE:
 * @note await deleteDirectory(path.join(__dirname, 'exampleDir'));
 * 
 * @param {*} directory 
 */
export async function deleteDirectory(directory) {
    try {
        await fs.promises.rmdir(directory);
    } catch (error) {
        // @ts-ignore
        console.error(`ERROR deleting directory: ${error.message}`);
    }
}

/**
 * @note USAGE:
 * @note await deleteDirectoryRecursive(path.join(__dirname, 'nonEmptyDir'));
 * 
 * @param {*} directory 
 */
export async function deleteDirectoryRecursive(directory) {
    try {
        await fs.promises.rm(directory, { recursive: true, force: true });
    } catch (error) {
        // @ts-ignore
        console.error(`ERROR deleting directory: ${error.message}`);
    }
}

/**
 * @note USAGE:
 * @note await copyDirectory(path.join(__dirname, 'sourceDir'), path.join(__dirname, 'destDir'));
 * 
 * @param {*} srcDir 
 * @param {*} destDir 
 */
export async function copyDirectory(srcDir, destDir) {
    await fs.promises.mkdir(destDir, { recursive: true });
    const ITEMS = await fs.promises.readdir(srcDir, { withFileTypes: true });

    await Promise.all(ITEMS.map(async (item) => {
        const SOURCE_PATH = path.join(srcDir, item.name);
        const DESTINATION_PATH = path.join(destDir, item.name);

        if (item.isDirectory()) {
            await copyDirectory(SOURCE_PATH, DESTINATION_PATH);
        } else {
            await fs.promises.copyFile(SOURCE_PATH, DESTINATION_PATH);
        }
    }));
}
