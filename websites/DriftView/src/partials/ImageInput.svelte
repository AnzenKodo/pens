<script lang="ts">
  import {getTagValue} from "@welshman/util"
  import {createEventDispatcher} from "svelte"
  import Input from "src/partials/Input.svelte"
  import Modal from "src/partials/Modal.svelte"
  import Spinner from "src/partials/Spinner.svelte"
  import Anchor from "src/partials/Anchor.svelte"
  import {listenForFile} from "src/util/html"
  import {uploadFiles, getSetting} from "src/engine"
  import {displayList} from "src/util/misc"

  export let icon = null
  export let value = null
  export let multi = false
  export let maxWidth = null
  export let maxHeight = null
  export let hostLimit = 1

  const urls = getSetting("nip96_urls").slice(0, hostLimit)
  const dispatch = createEventDispatcher()

  let input, loading
  let isOpen = false

  $: {
    if (input) {
      listenForFile(input, async inputFiles => {
        if (inputFiles) {
          loading = true

          try {
            const tags = await uploadFiles(urls, inputFiles, {
              maxWidth,
              maxHeight,
            })

            // For inputs that only want one file
            value = getTagValue("url", tags)

            if (value) {
              dispatch("change", value)
            }
          } finally {
            isOpen = false
            loading = false
          }
        }
      })
    }
  }

  const decline = () => {
    isOpen = false
  }
</script>

<div class="flex gap-2">
  {#if icon}
    <Input type="text" class="flex-grow" bind:value placeholder="https://">
      <i slot="before" class={`fa fa-${icon}`} />
    </Input>
  {/if}
  <div
    on:click={() => {
      isOpen = true
    }}>
    <slot name="button">
      <div class="flex">
        <Anchor button>
          <i class="fa fa-upload" />
        </Anchor>
      </div>
    </slot>
  </div>
</div>

{#if isOpen}
  <Modal mini onEscape={decline}>
    {#if loading}
      <Spinner delay={0}>Uploading files using: DriftNet</Spinner>
    {:else}
      <h1 class="staatliches text-2xl">Upload a File</h1>
      <div class="flex flex-col gap-2">
        <p>Click below to select a file to upload.</p>
        <p class="text-gray-3 text-sm">
          <i class="fa fa-warning" />
          Note that images are stored unencrypted and publicly accessible.
        </p>
      </div>
      <input multiple={multi} type="file" bind:this={input} />
    {/if}
  </Modal>
{/if}
