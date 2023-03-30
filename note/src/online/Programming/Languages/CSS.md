# CSS

[SASS](CSS%208946e12a95f04e3490bd9c09bfb99d1e/SASS%20d57c9cbb233644a3a615a487f4cdf949.md)

- BEM Method

    ```css
    /* Block component */
    .btn {}
    /* Element that depends upon the block */
    .btn__price {}
    /* Modifier that changes the style of the block */
    .btn--orange {}
    .btn--big {}
    ```

- Dark Mode Setting

    ```css
    :root {
      color-scheme: light dark; /* both supported */
    }
    ```

- Image Dark
    - Apply the filter directly on the body tag.

        ```css
        body.dark-theme img {
          filter: brightness(.8) contrast(1.2);
        }
        ```

    - Or apply it via media query.

        ```css
        @media (prefers-color-scheme: dark) {
          img {
            filter: brightness(.8) contrast(1.2);
          }
        }
        ```

- Image prefer Dark

    ```html
    <picture>
      <!-- Use this image if the user's OS setting is light or unset -->
      <source srcset="photo-light.png" media="(prefers-color-scheme: light) or (prefers-color-scheme: no-preference)">
      <!-- Use this image if the user's OS setting is dark -->
      <source srcset="photo-dark.png" media="(prefers-color-scheme: dark)">
    </picture>
    ```

- Non-standard attributes, dataset

    ```css
    <style>
      /* styles rely on the custom attribute "order-state" */
      .order[order-state="new"] {
        color: green;
      }

      .order[order-state="pending"] {
        color: blue;
      }

      .order[order-state="canceled"] {
        color: red;
      }
    </style>

    <div class="order" order-state="new">
      A new order.
    </div>

    <div class="order" order-state="pending">
      A pending order.
    </div>

    <div class="order" order-state="canceled">
      A canceled order.
    </div>
    ```
