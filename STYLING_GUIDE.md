# Styling Guide

**Note that we were talking about C++**

We are using clang-format and prettier to format the C++ files(.cpp) and markdown files(.md) automatically.

Specifically, we are following Google's C++ style.

The following scripts can be used to format your code.

```bash
npm install .
git config clangFormat.binary node_modules/.bin/clang-format
git config clangFormat.style file

# check whether needs formatting (optional)
npm run lint

# format automatically
npm run format
```
