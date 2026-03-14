use std::fs;

struct Point {
    x: usize,
    y: usize
}

fn load_input(path: &str) -> Vec<Vec<char>> {
    let content = fs::read_to_string(path).expect("Missing read gile");
    let data: Vec<Vec<char>> = content.lines()
        .map(|s| s.chars()
            .collect()
        ).collect();

    return data;
}

fn print_map(map: &Vec<Vec<char>>) {
    for row in map {
        for c in row {
            print!("{c}");
        }
        println!("");
    }
}

fn can_take_pape(map: &Vec<Vec<char>>, x: i32, y: i32, at_least: i32) -> bool{
    if map[y as usize][x as usize] != '@' {return false;}

    let mut count: i32 = -1;
    for _y in y-1..=y+1 {
        if _y < 0 || _y as usize >= map.len() {
            count += 3;
        } else {
            for _x in x-1..=x+1 {
                if _x < 0 || _x as usize >= map[0].len() || map[_y as usize][_x as usize] != '@' {
                    count += 1;
                }
            }
        }
    }

    return count >= at_least;
}

fn remove_from_map(map: &mut Vec<Vec<char>>, points: &Vec<Point>){
    for point in points {
        map[point.y][point.x] = '.';
    }
}


fn main() {
    // let mut data = load_input("example.txt");
    let mut data = load_input("input.txt");

    let y_size = data.len();
    let x_size = data[0].len();

    let mut sum: u64 = 0;
    'part_sum: loop {
        let mut part_sum: u64 = 0;
        let mut to_remove: Vec<Point> = Vec::new();
        for y in 0..y_size {
            for x in 0..x_size {
                if can_take_pape(&data, x as i32, y as i32, 4) {
                    part_sum += 1;
                    let point = Point{
                        x: x,
                        y: y
                    };
                    to_remove.push(point);
                }
            }
        }
        println!("Remove: {}", part_sum);
        sum += part_sum;
        if part_sum == 0 {break 'part_sum;}

        remove_from_map(&mut data, &to_remove);
    }

    print_map(&data);
    println!("Sum: {sum}");
}
