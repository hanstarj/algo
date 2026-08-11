---
name: leetcode
description: Scaffold a LeetCode problem in this repo. Takes a problem number or URL plus a language (rust or cpp) and generates the solution-file boilerplate — header link, official function signature fetched from LeetCode, and tests wired to the problem's examples. Use when the user wants to start, scaffold, or generate boilerplate for a LeetCode problem.
argument-hint: <number|url> [rust|cpp]
---

# LeetCode boilerplate

Generate the solution-file boilerplate for: $ARGUMENTS

Boilerplate only — do NOT solve the problem. The function body stays `todo!()` in Rust and `return {};` in C++. Do not commit.

## 1. Parse arguments

- Problem: a number (`27`) or a URL (`https://leetcode.com/problems/remove-element/description/` — the slug is the path segment after `/problems/`).
- Language: `rust` or `cpp`. If not given, ask the user which one.

## 2. Fetch problem data

If given only a number, resolve the slug (pick the result whose `questionFrontendId` matches the number exactly):

```bash
curl -s 'https://leetcode.com/graphql/' -H 'Content-Type: application/json' -H 'User-Agent: Mozilla/5.0' \
  --data '{"query":"query($filters:QuestionListFilterInput){problemsetQuestionList:questionList(categorySlug:\"\",limit:10,skip:0,filters:$filters){questions:data{questionFrontendId titleSlug title}}}","variables":{"filters":{"searchKeywords":"NUMBER"}}}'
```

Fallback if that query errors (schema drift): `curl -s 'https://leetcode.com/api/problems/all/'` and filter `stat_status_pairs` for `stat.frontend_question_id == NUMBER`, taking `stat.question__title_slug`.

Then fetch details, saving to the scratchpad (the response is large):

```bash
curl -s 'https://leetcode.com/graphql/' -H 'Content-Type: application/json' -H 'User-Agent: Mozilla/5.0' \
  --data '{"query":"query($slug:String!){question(titleSlug:$slug){questionFrontendId title titleSlug content codeSnippets{langSlug code}}}","variables":{"slug":"SLUG"}}'
```

Use from the response:
- `questionFrontendId` → N, `title`, `titleSlug`
- `codeSnippets` entry with the matching `langSlug` (`rust` or `cpp`) → the official signature
- `content` → HTML problem statement; rendered into the file's header comment, and each Example's Input/Output pair also drives the tests

If a file for problem N already exists under the target language, stop and tell the user instead of overwriting.

## 3. Rust

File: `rust/problems/src/lc<N>_<title_snake>.rs`, where `<title_snake>` is the full title lowercased with punctuation dropped and spaces/hyphens as `_` (e.g. `lc27_remove_element.rs`).

```rust
//! [LeetCode <N>: <Title>](https://leetcode.com/problems/<slug>)
//!
//! <description paragraphs>
//!
//! # Example 1
//!
//! ```text
//! Input: <...>
//! Output: <...>
//! Explanation: <...>
//! ```
//!
//! <remaining examples>
//!
//! # Constraints
//!
//! - <constraint>

pub fn <name>(<params>) -> <ret> {
    todo!()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn all() {
        assert_eq!(<name>(<example 1 input>), <example 1 output>);
        assert_eq!(<name>(<example 2 input>), <example 2 output>);
    }
}
```

- The header doc comment carries the full problem statement converted from the `content` HTML to markdown: description paragraphs, every example (inside ```` ```text ```` fences so rustdoc doesn't compile them), and the constraints list. Strip tags, `<code>x</code>` → `` `x` ``, `<sup>n</sup>` → `^n`, decode HTML entities, wrap lines at ~100 chars.
- Signature comes from the `rust` code snippet: strip the `impl Solution { }` wrapper and all comments, dedent, keep `pub fn` at top level.
- Problems with auxiliary types (`ListNode`, `TreeNode`): define the struct at top level with the snippet's derives, and add a `fn build(...)` helper inside `mod tests` to construct instances — see `lc21_merge_two_sorted_lists.rs`.
- One `assert_eq!` per example from the statement. If the output needs adaptation (in-place mutation, order-independent comparison), add a small `check` helper in `mod tests` like `lc27_remove_element.rs` does.
- No comments anywhere in the file besides the header doc comment.
- Register in `rust/problems/src/lib.rs`: insert `pub mod lc<N>_<title_snake>;` in numeric order, respecting the existing blank-line grouping.
- Verify: `cd rust && cargo check -p problems --tests`. An `unused variable` warning for each parameter is expected with a `todo!()` body — leave the names unprefixed. Do not run the tests; they panic on `todo!()` by design.

## 4. C++

File: `cpp/problems/<N>_<ShortName>.cpp`, where `<ShortName>` is a shortened PascalCase title in the spirit of existing files (`42_TrapWater.cpp`, `989_AddToArray.cpp`).

```cpp
// https://leetcode.com/problems/<slug>/
//
// <description paragraphs>
//
// Example 1:
// Input: <...>
// Output: <...>
// Explanation: <...>
//
// <remaining examples>
//
// Constraints:
// - <constraint>

#include <vector>
<ret> <PascalName>(<params>)
{
    return {};
}

#include <iostream>
int main()
{
    <build example 1 input, call <PascalName>, print the result>
    return 0;
}
```

- The header comment carries the full problem statement, converted from the `content` HTML with the same rules as the Rust header, as `//` lines.
- Signature types come from the `cpp` code snippet, but as a free function (no `class Solution`), PascalCase name, `std::`-qualified types, no `using namespace`, Allman braces.
- Include only the headers the signature needs, placed like existing files: containers at the top, `<iostream>` just above `main`.
- `main` runs example 1 and prints the result, like `989_AddToArray.cpp`.
- Verify: `clang++ -std=c++17 -fsyntax-only cpp/problems/<file>.cpp`.

## 5. Report

Tell the user the file path and that the tests cover the problem's examples, ready for them to implement the solution.
