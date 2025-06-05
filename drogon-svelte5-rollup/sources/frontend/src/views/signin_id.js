import { mount } from "svelte";
import SignInId from "./svelte/signin_id.svelte";

export default mount(SignInId, {
    target: document.body
});
