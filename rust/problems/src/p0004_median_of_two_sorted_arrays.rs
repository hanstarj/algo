pub fn find_median_sorted_arrays(n1: &[i32], n2: &[i32]) -> f64 {
    if n1.len() > n2.len() {
        return find_median_sorted_arrays(n2, n1);
    }

    let (c1, c2) = (n1.len(), n2.len());
    let c3 = c1 + c2;
    let odd = c3 % 2 == 1;

    let mut start = 0;
    let mut end = c1 + 1;
    while start < end {
        let b1 = (start + end) / 2;
        if b1 > c3 / 2 {
            end = b1;
            continue;
        }
        let b2 = c3 / 2 - b1;

        let n1_left_max = if b1 > 0 { n1[b1 - 1] } else { i32::MIN };
        let n1_right_min = if b1 < c1 { n1[b1] } else { i32::MAX };
        let n2_left_max = if b2 > 0 { n2[b2 - 1] } else { i32::MIN };
        let n2_right_min = if b2 < c2 { n2[b2] } else { i32::MAX };

        if n1_left_max > n2_right_min {
            end = b1;
        } else if n2_left_max > n1_right_min {
            start = b1 + 1;
        } else if odd {
            return n1_right_min.min(n2_right_min) as f64;
        } else {
            return (n1_left_max.max(n2_left_max) as f64 + n1_right_min.min(n2_right_min) as f64)
                * 0.5;
        }
    }

    0.0
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn even_total() {
        assert_eq!(find_median_sorted_arrays(&[0, 1], &[2, 3]), 1.5);
        assert_eq!(find_median_sorted_arrays(&[1, 2], &[3, 4]), 2.5);
    }

    #[test]
    fn odd_total() {
        assert_eq!(find_median_sorted_arrays(&[1, 3], &[2]), 2.0);
        assert_eq!(find_median_sorted_arrays(&[1, 2, 3, 4, 5], &[6]), 3.5);
    }

    #[test]
    fn one_side_empty() {
        assert_eq!(find_median_sorted_arrays(&[], &[1, 2, 3]), 2.0);
        assert_eq!(find_median_sorted_arrays(&[2], &[]), 2.0);
    }

    #[test]
    fn disjoint_ranges() {
        assert_eq!(find_median_sorted_arrays(&[1, 2, 3], &[100, 200]), 3.0);
        assert_eq!(find_median_sorted_arrays(&[100, 200], &[1, 2, 3]), 3.0);
    }
}
