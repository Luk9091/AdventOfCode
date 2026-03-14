use std::fs;

fn read_file(file: String) -> Vec<String>{
    let content = fs::read_to_string(file).expect("File read error");
    let data: Vec<String> = content.lines()
        .map(|s| s.to_string())
        .collect();

    return data;
}

fn decode(instruction: &String, start_position: i32, base: i32) -> (i32, i32){
    let mut next_position : i32;
    let move_position: i32 = instruction[1..].trim().parse().expect("Invalid convert");
    let direction = instruction.chars().nth(0).expect("");
    let mut zero_cnt = 0;

    if  direction == 'L' {
        next_position = start_position - move_position;
    } else {
        next_position = start_position + move_position;
    }

    if next_position <= 0{
        zero_cnt = (next_position / 100).abs();
        if start_position != 0 {
            zero_cnt += 1;
        }
        next_position = (base + (next_position % base)) % base;
    } else if next_position >= 100 {
        zero_cnt = next_position / 100;

        next_position = next_position % base;
    }

    return (next_position, zero_cnt);
}


fn main() {
    println!("Hello, world!");

    let instructions = read_file(String::from("input.txt"));
    let mut position: i32 = 50;
    let mut zero_cnt = 0;
    for instruction in &instructions {
        let additional;
        (position, additional) = decode(instruction, position, 100);

        zero_cnt += additional;
        println!("Dial rotated: {instruction} -> {position},  \tadditional: {additional}");
    }
    println!("Zero cnt: {zero_cnt}");
}