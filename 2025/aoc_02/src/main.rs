use std::{fs, str::FromStr};

#[derive(Debug)]
struct Range{
    start: u64,
    end: u64
}

impl FromStr for Range {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let (start_str, end_str) = s.split_once('-')
            .ok_or("Missing '-'")?;

        Ok(Range {
            start: start_str.parse().expect("Parse error"),
            end: end_str.parse().expect("Parse error"),
        })
    }
}

fn read_file(file: &str) -> Vec<Range> {
    let content = fs::read_to_string(file)
        .expect("Invalid path to file");

    let data: Vec<Range> = content.split(',')
        .map(|s| s.parse().expect("String parse error"))
        .collect();
    return data;
}

fn find_duble(value: &u64) -> bool {
    let value_str: String = value.to_string();
    let len = value_str.len();
    if  len % 2 != 0 {
        return false;
    }

    let sub = value_str[0..len/2].to_string();
    return sub == value_str[len/2..];
}

fn find_multiple(value: &u64) -> bool {
    let value_str: String = value.to_string();
    let len = value_str.len();
    // let half_len = len / 2;


    'select_sub: for sub_len in 1..=len/2 {
        let sub = value_str[0..sub_len].to_string();

        for i in (sub_len..len).step_by(sub_len) {
            if i + sub_len > len{
                continue 'select_sub;
            }

            let check = value_str[i..i+sub_len].to_string();
            if sub != check {
                continue 'select_sub;
            }
        }

        return true;
    }

    return false;
}


fn main() {
    println!("Hello, world!");


    // let list_of_range = read_file("example.txt");
    let list_of_range = read_file("input.txt");
    let mut sum = 0;
    for range in &list_of_range {
        println!("Check range: {}-{}", range.start, range.end);

        for value in range.start..=range.end {
            // if find_duble(&value) { // First star
            if find_multiple(&value) { // Second star
                println!("\tInvalid ID: {}", value);
                sum += value;
            }
        }
    }

    println!("End sum: {}", sum);
}
