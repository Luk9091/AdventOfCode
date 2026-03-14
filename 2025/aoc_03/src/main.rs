use std::fs;

fn read_input(path: &str) -> Vec<Vec<u32>> {
    let content = fs::read_to_string(path).expect("File read error");
    let data: Vec<Vec<u32>> = content.lines()
        .map(|s| s.chars()
            .map(|n| n.to_digit(10).expect("NoN"))
            .collect()
        )
        .collect();
    return data;
}

fn find_right_max(line: &Vec<u32>, tail: usize) -> usize{
    let mut max = 0;
    let mut index = 0;
    for i in 0..line.len() - tail {
        if line[i] > max {
            max = line[i];
            index = i;
        }
    }

    return index;
}

fn find_left_max(line: &Vec<u32>, tail: usize) -> usize{
    let mut max = 0;
    let mut index = 0;
    for i in tail..line.len() {
        if line[i] >= max {
            max = line[i];
            index = i;
        }
    }

    return index;
}

fn star_1(data: &Vec<Vec<u32>>){
    println!("##############################");
    println!("First star");
    println!("##############################");
    let mut sum = 0;

    for line in data {
        let right = find_right_max(&line, 1);
        let left = find_left_max(&line, right+1);
        let connection = line[right] * 10 + line[left];

        println!("Next line");
        println!("\tright:   {}:{right}", line[right]);
        println!("\tleft:    {}:{left}", line[left]);
        println!("\tconnect: {connection}");
        sum += connection;
    }

    println!("Sum: {sum}");
}

fn star_2(data: Vec<Vec<u32>>){
    println!("##############################");
    println!("Second star");
    println!("##############################");

    let mut sum: u64 = 0;
    for mut line in data{
        let mut connection: u64 = 0;
        for i in 0..12 {
            let index = find_right_max(&line, 11 - i);
            connection = connection * 10 + line[index] as u64;
            for i in 0..=index{
                line[i] = 0;
            }
        }
        println!("Connection: {connection}");
        sum += connection;
    }

    println!("Sum: {sum}");
}

fn main() {
    println!("Hello, world!");
    // let data = read_input("example.txt");
    let data = read_input("input.txt");
    star_1(&data);
    star_2(data);
}


// 43 43 34 23 42 78