<script>
    import { onMount } from "svelte";
    import { PROJECT_IS_DEBUG } from "@libfrontend/config";

    // @ts-ignore
    let backendMessage = $state(BACKEND_MESSAGE);

    onMount(async() => {
        if (PROJECT_IS_DEBUG) {
            // 
        }
    });

    function hintHelp() {
        alert("email: dg@drogon.org\npassword: drogonframework");
    }
</script>

<section class="section">
    <form class="form fcenter" action="/id/sign-in" method="post">
        {#if backendMessage.length > 0}
        <p>{backendMessage}</p>
        {:else}
        <p></p>
        {/if}

        <input type="email" placeholder="email" name="email" required>

        <input type="password" placeholder="kata sandi" name="password" required>

        <br>

        <div>
            <button type="submit">
                signin
            </button>
            <button onclick={hintHelp}>
                pentunjuk
            </button>
        </div>

        <br>

        <a href="/id/home">beranda</a>
    </form>
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
