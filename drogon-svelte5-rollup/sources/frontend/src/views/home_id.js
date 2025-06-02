import { mount } from "svelte";
import WwwHomeId from "./svelte/home_id.svelte";

export default mount(WwwHomeId, {
    target: document.body
});
