//! [LeetCode 15: Roman to Integer](https://leetcode.com/problems/roman-to-integer/)

pub fn roman_to_int(s: String) -> i32 {
    let mut v: i32 = 0;
    for c in s.chars() {
        let d = match c {
            'I' => 1,
            'V' => 5,
            'X' => 10,
            'L' => 50,
            'C' => 100,
            'D' => 500,
            'M' => 1000,
            _ => unreachable!(),
        };
        v += d - (v % d) * 2;
    }

    v
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn all() {
        assert_eq!(roman_to_int("I".to_string()), 1);
        assert_eq!(roman_to_int("III".to_string()), 3);
        assert_eq!(roman_to_int("IV".to_string()), 4);
        assert_eq!(roman_to_int("V".to_string()), 5);
        assert_eq!(roman_to_int("VI".to_string()), 6);
        assert_eq!(roman_to_int("VIII".to_string()), 8);
        assert_eq!(roman_to_int("IX".to_string()), 9);
        assert_eq!(roman_to_int("X".to_string()), 10);
        assert_eq!(roman_to_int("XIII".to_string()), 13);
        assert_eq!(roman_to_int("XIV".to_string()), 14);
        assert_eq!(roman_to_int("XIX".to_string()), 19);
        assert_eq!(roman_to_int("LVIII".to_string()), 58);
        assert_eq!(roman_to_int("MCMXCIV".to_string()), 1994);
    }
}
