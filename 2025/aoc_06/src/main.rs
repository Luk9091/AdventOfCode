use std::{fs};

fn transpose(matrix: &[String]) -> Vec<String>{
    let cols = matrix[0].len();
    let rows = matrix.len();

    let t: Vec<Vec<char>> = (0..cols)
        .map(|x| {
            (0..rows)
                .map(|y| matrix[y].chars().nth(x).expect("Not char"))
                .collect()
        }).collect();

    let trans: Vec<String> = t.iter()
        .map(|v| v.iter().cloned().collect())
        .collect();

    let trans_str: Vec<String> = trans
        .split(|s| s.trim().is_empty())
        .map(|chunk| chunk.join(" "))
        .filter(|s| !s.is_empty())
        .collect();

    return trans_str;
}

fn load_input(path: &str) -> (Vec<Vec<i64>>, Vec<char>, Vec<Vec<i64>>) {
    let content = fs::read_to_string(path).expect("File error");
    let data: Vec<String> = content.lines()
        .map(|s| s.to_string())
        .collect();
    // println!("{:?}", data);

    let numbers: Vec<Vec<i64>> = data[..data.len()-1].iter()
        .map(
            |s| s.split_whitespace()
                .map(|i| i.parse().expect("Parse error"))
                .collect()
        )
        .collect();

    // transpose(&data[..data.len() - 1]);
    let trans = transpose(&data[..data.len()-1]);
    // println!("Transposition string:");
    // println!("{:?}", trans);
    let transpose_number = trans.iter()
        .map(|s| s.split_whitespace()
            .map(|i| i.parse().expect("Parse error"))
            .collect()
        )
        .collect();

    let operators: Vec<char> = data.last().iter()
        .flat_map(|s| s.split_whitespace())
        .flat_map(|o| o.chars())
        .collect();


    // println!("Numbers: {:?}", numbers);
    // println!("Operators {:?}", operators);
    return (numbers, operators, transpose_number);
}


fn calculate_vertical(numbers: &Vec<Vec<i64>>, operation: char, index: usize) -> i64 {
    let mut value = numbers[0][index];
    print!("\t{value} ");
    for i in 1..numbers.len() {
        match operation {
            '*' => {
                print!("* ");
                value *= numbers[i][index];
            },
            '+' => {
                print!("+ ");
                value += numbers[i][index];
            }
            _ => {
                println!("Operation Error");
                return 0;
            },
        }
        print!("{} ", numbers[i][index]);
    }
    println!("= {value}");

    return value;
}

fn calculate_horizontal(numbers: &Vec<i64>, operation: char) -> i64 {
    let mut value = numbers[0];
    print!("\t{value} ");
    for i in 1..numbers.len() {
        match operation {
            '*' => {
                print!("* ");
                value *= numbers[i];
            },
            '+' => {
                print!("+ ");
                value += numbers[i];
            }
            _ => {
                println!("Operation Error");
                return 0;
            },
        }
        print!("{} ", numbers[i]);
    }
    println!("= {value}");

    return value;

}



fn main() {
    // let (numbers, operations, trans) = load_input("example.txt");
    let (numbers, operations, trans) = load_input("input.txt");

    let mut sum = 0;
    for i in 0..operations.len() {
        let value= calculate_vertical(&numbers, operations[i], i);
        sum += value;
    }
    println!("Sum: {sum}");

    println!("Transpose: {:?}", trans);
    let mut sum: i64 = 0;
    for i in  0..operations.len() {
        sum += calculate_horizontal(&trans[i], operations[i], );
    }
    println!("Transpose sum: {sum}");
}
