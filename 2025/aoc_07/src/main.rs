use std::{collections::{BTreeMap, BTreeSet}, fs};

fn load_input(path: &str) -> Vec<String> {
    let file  = fs::read_to_string(path).expect("File {} don't exists!");
    file.lines()
        .map(|s| s.to_string())
        // .filter(|s| s.contains("^") || s.contains("S"))
        .collect()
}

fn split_location(line: &String, split_char: char) -> BTreeSet<usize> {
    let mut set: BTreeSet<usize> = BTreeSet::new();
    for (i, c) in line.chars().enumerate() {
        if c == split_char {
            // println!("i: {i}, c: {c}");
            set.insert(i);
        }
    }
    set
}
fn make_neighbour(set: BTreeSet<usize>, old: BTreeSet<usize>) -> BTreeSet<usize> {
    let mut neighbour = BTreeSet::new();
    let old = &old - &set;
    for value in set.iter() {
        neighbour.insert(value-1);
        neighbour.insert(value+1);
    }
    &neighbour | &old
}

fn count_split(line: &String, lasers: &BTreeSet<usize>) -> i32{
    let mut count = 0;
    for index in lasers.iter() {
        if line.chars().nth(*index).unwrap() == '^' {
            count += 1;
        }
    }
    count
}

fn main() {
    // let lines = load_input("example.txt");
    let lines = load_input("input.txt");

    let start = split_location(&lines[0], 'S');

    let last = lines.iter()
        .fold((start, 0), |(old, sum),  line| {
            if line.contains("^") /*|| line.contains("S")*/ {
                let count = count_split(&line, &old) + sum;
                let neighbour = make_neighbour(split_location(&line, '^'), old);
                println!("{} | {:?} \t {}", line, neighbour, neighbour.len());
                (neighbour, count)
            } else {
                (old, sum)
            }
        });

    println!("Sum: {}", last.1);
}
