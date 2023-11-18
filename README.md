# uhtml - Micro HTML Library

uhtml is a lightweight C library for parsing and rendering HTML structures. It is designed to be simple, easy to use, and suitable for resource-constrained environments.

## Features

- **Simplicity:** uhtml provides a straightforward API for parsing HTML and working with the resulting DOM (Document Object Model).
- **Lightweight:** Designed to be lightweight, making it suitable for embedded systems or environments with limited resources.
- **Basic CSS Support:** uhtml includes basic support for parsing and applying CSS styling to elements.

## Usage

1. **Include uhtml in Your Project:**
   Clone this repository or download the uhtml files and include them in your project.

2. **Include the Header File:**
   Include the `uhtml.h` header file in your source code:

   ```c
   #include "uhtml.h"
   ```

3. **Parse HTML:**
   Use the `parseHTML` function to parse an HTML string:

   ```c
   char html[] = "<html><body><h1>Hello, uhtml!</h1></body></html>";
   Node* domTree = parseHTML(html);
   ```

4. **Manipulate the DOM:**
   Use the provided functions to manipulate the DOM:

   ```c
   // Example: Add a new element to the DOM
   Node* newElement = createNode("p", "This is a paragraph", "");
   addChild(domTree, newElement);
   ```

5. **Render the DOM:**
   Use the rendering functions to display or save the modified HTML:

   ```c
   // Example: Render the modified DOM
   renderDOM(domTree);
   ```

6. **Free Memory:**
   Don't forget to free the memory when you're done:

   ```c
   freeDOM(domTree);
   ```

## Building

uhtml is a header-only library. Simply include the `uhtml.h` file in your project.

## Example

Here's a simple example of parsing, modifying, and rendering HTML using uhtml:

```c
#include <stdio.h>
#include "uhtml.h"

int main() {
    char html[] = "<html><body><h1>Hello, uhtml!</h1></body></html>";
    Node* domTree = parseHTML(html);

    // Modify the DOM
    Node* newElement = createNode("p", "This is a paragraph", "");
    addChild(domTree, newElement);

    // Render the modified DOM
    renderDOM(domTree);

    // Free memory
    freeDOM(domTree);

    return 0;
}
```

## License

uhtml is released under the MIT License. See [LICENSE](LICENSE) for details.
