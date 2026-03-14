use std::{collections::{BTreeSet}, fs};

fn load_input(path: &str) -> Vec<String> {
    let file  = fs::read_to_string(path).expect("File don't exists!");
    file.lines()
        .map(|s| s.to_string())
        // .filter(|s| s.contains("^") || s.contains("S"))
        .collect()
}

fn find_first_element(line: &str) -> BTreeSet<usize>{
    let mut set = BTreeSet::new();
    let start_position = line.find("S")
        .expect("Cannot find first position");
    set.insert(start_position);
    set
}

fn main() {
    // let lines = load_input("example.txt");
    let lines = load_input("input.txt");

    let start = find_first_element(&lines[0]);


    let last = lines.iter()
        .skip(1)
        .fold((start, 0), |(previous_line, sum),  line| {
            let mut count = 0;
            let mut next_line = BTreeSet::new();
            for index in previous_line {
                if line.as_bytes()[index] == b'^' {
                    next_line.insert(index-1);
                    next_line.insert(index+1);
                    count += 1;
                } else {
                    next_line.insert(index);
                }
            }
            (next_line, sum + count)
        });

    println!("Sum: {}", last.1);
}
