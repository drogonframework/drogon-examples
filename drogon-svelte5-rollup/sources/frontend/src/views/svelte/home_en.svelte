<script>
    import { onMount } from "svelte";
    import EndUser from "@libfrontend/components/end_user.svelte";
    import { PROJECT_IS_DEBUG } from "@libfrontend/config";

    /**
     * @type {import("svelte").SvelteComponent<Record<string, never>, never, never> & { getUsername: () => string; getIsSignIn: () => boolean; } & { $$bindings: ""; }}
     */
    let _user;

    let username = $state("guest");
    let is_signin = $state(false);

    onMount(async() => {
        username = _user.getUsername();
        is_signin = _user.getIsSignIn();

        if (PROJECT_IS_DEBUG) {
            console.log(`DEBUG: username: ${username}`);
        }
    });
</script>

<EndUser bind:this={_user} />

<section class="section">
    <div class="fcenter">
        <p class="text-center">www home - en</p>
        {#if is_signin}
        <br>
        <p>hi, {username}</p>
        {/if}
    </div>
</section>

<style lang="scss">
    .section {
        display: flex;
        justify-content: center;
        align-items: center;
        height: 100vh;
        min-height: 100vh;
    }

    .fcenter {
        display: flex;
        flex-direction: column;
        align-items: center;
        gap: 1em;
    }
</style>
