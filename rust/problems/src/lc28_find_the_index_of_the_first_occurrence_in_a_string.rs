//! https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string

pub fn str_str(haystack: String, needle: String) -> i32 {
    // using built-ins:
    // haystack.find(&needle).map_or(-1, |i| i as i32)
    //
    // manual:
    if haystack.len() >= needle.len() {
        for i in 0..(haystack.len() - needle.len() + 1) {
            if haystack[i..i + needle.len()] == needle {
                return i as i32;
            }
        }
    }

    -1
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        assert_eq!(str_str("apple".into(), "apple".into()), 0);
        assert_eq!(str_str("applebook".into(), "apple".into()), 0);
        assert_eq!(str_str("applebook".into(), "book".into()), 5);
        assert_eq!(str_str("applebookapple".into(), "apple".into()), 0);
        assert_eq!(str_str("applebookbook".into(), "book".into()), 5);
        assert_eq!(str_str("applebookbook".into(), "book".into()), 5);
        assert_eq!(str_str("applebababook".into(), "babo".into()), 7);
        assert_eq!(str_str("applebook".into(), "cat".into()), -1);
        assert_eq!(str_str("applebookcar".into(), "cat".into()), -1);
        assert_eq!(str_str("app".into(), "apple".into()), -1);
    }
}
