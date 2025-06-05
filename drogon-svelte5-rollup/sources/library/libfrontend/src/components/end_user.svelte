<script>
    /*
    NOTE:
    - when importing scss directly to component:
        - you can not use import on 1 core scss file as core, for instance:
            - importing main.scss
            - where the main.scss is use another `@use` or `@import`
            - it will not refresh the change from that updated scss file, for now
    */
    import "@libfrontend/scss/core.scss";
    import "@libfrontend/scss/text.scss";
    import "@libfrontend/scss/tag-body.scss";
    import { onMount } from "svelte";
    import { PROJECT_IS_DEBUG } from "@libfrontend/config";
    import CONFIG_PROJECT from "../../../../../.config/config.project.json";

    /** @type {string} */
    const DEFAULT_USERNAME = CONFIG_PROJECT.default.non_signin_username;

    /**
     * @brief current username, assign from BACKEND_USERNAME
     * 
     * @note BACKEND_USERNAME were ignored, but must exists for control
     * @note check BACKEND_USERNAME inside www_svelte.csp
     * 
     * @note you may also check what allowed username string if stored them
     * @note for example, don't allow to use `root`, `admin`, or default `guest`
     * 
     * @note unless specific condition
     * 
     * @type {string}
    */
    // @ts-ignore
    const USERNAME = $state((BACKEND_USERNAME === "" || BACKEND_USERNAME === DEFAULT_USERNAME) ? DEFAULT_USERNAME : BACKEND_USERNAME);

    /**
     * @note indicate if the enduser is signin or not
     * 
     * @type {boolean}
    */
    // @ts-ignore
    const IS_SIGN_IN = $state((USERNAME === DEFAULT_USERNAME || USERNAME === "") ? false : true);

    const ENDUSER_LOCAL_STORAGE_KEY = {
        language: "_lang"
    };


    /**
     * @type {string | null}
     */
    let lang = $state(null);

    onMount(async() => {
        lang = localStorage.getItem(ENDUSER_LOCAL_STORAGE_KEY.language);

        if (lang === null || lang === "") {
            lang = "en";
        }

        localStorage.setItem(ENDUSER_LOCAL_STORAGE_KEY.language, lang);

        // do something else for this?

        // debug below
        if (PROJECT_IS_DEBUG) {
            console.log("DEBUG: end_user.svelte loaded");
        }
    });

    /**
     * @returns {string} 
     */
    export function getUsername() {
        return USERNAME;
    }

    /**
     * @returns {boolean}
     */
    export function getIsSignIn() {
        return IS_SIGN_IN;
    }
</script>

<div class="parent">
    <div class="child-left">
        <p>{USERNAME}</p>
    </div>
    <div class="child-right">
        {#if IS_SIGN_IN}
        <a href="/{lang}/sign-out">
            sign-out
        </a>
        {:else}
        <a href="/{lang}/sign-in">
            sign-in
        </a>
        {/if}
    </div>
</div>

<style lang="scss">
    .parent {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 1rem;
    }
</style>
