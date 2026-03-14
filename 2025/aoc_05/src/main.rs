use std::{cmp::min, cmp::max, fs, str::FromStr};

#[derive(Debug, Eq, PartialEq, Clone)]
struct Range {
    min: u64,
    max: u64,
}

impl FromStr for Range {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let (start_str, end_str) = s.split_once('-')
            .ok_or("Missing '-'")?;

        Ok(Range {
            min: start_str.parse().expect("Parse error"),
            max: end_str.parse().expect("Parse error"),
        })
    }
}

impl Range {
    fn diff(&self) -> u64 {
        self.max - self.min + 1
    }

    fn inside(&self, a: &Range) -> bool {
        a.min >= self.min && a.min <= self.max || a.max >= self.min && a.max <= self.max
    }

    fn expand(&mut self, a: &Range){
        self.min = min(self.min, a.min);
        self.max = max(self.max, a.max);
    }
}

fn load_data(path: &str) -> (Vec<Range>, Vec<u64>) {
    let content = fs::read_to_string(path).expect("Missing file");
    let (ranges_str, ids_str) = content.split_once("\n\n").expect("Split error");

    let ranges: Vec<Range> = ranges_str.lines()
        .map(|s| s.parse().expect("String parse error"))
        .collect();

    let ids: Vec<u64> = ids_str.lines()
        .map(|s| s.parse().expect("String to id error"))
        .collect();

    return (ranges, ids);
}

fn is_fresh(id: u64, ranges: &Vec<Range>) -> bool{
    for range in ranges {
        if id >= range.min && id <= range.max {return true;}
    }
    return false;
}

fn remove_duplicates(ranges: &Vec<Range>) -> (Vec<Range>, u32){
    let mut news: Vec<Range> = Vec::new();
    let mut cnt = 0;

    'next: for to_check in ranges {
        println!("Check: {:?}", to_check);
        for new in &mut news {
            if to_check.inside(new) || new.inside(to_check){
                println!("\tinside: {:?}", new);
                new.expand(to_check);
                cnt += 1;
                continue 'next;
            }
        }
        if !news.contains(to_check) {
            news.push(to_check.clone());
        }
    }

    return (news, cnt);
}



fn main() {
    // let (ranges, ids) = load_data("example.txt");
    let (ranges, ids) = load_data("input.txt");

    // println!("Ranges: {:?}", ranges);
    // println!("Ids: {:?}", ids);

    let mut cnt = 0;
    for id in ids {
        if is_fresh(id, &ranges) {
            cnt += 1;
        }
    }
    println!("Count fresh: {cnt}");

    let mut cnt_inside = 0;
    let mut new: u32 = 1;
    let mut ranges = ranges.clone();
    let mut iteration = 1;
    while new != 0 {
        println!("Iteration: {iteration}");
        (ranges, new) = remove_duplicates(&ranges);
        iteration += 1;
    }

    // println!("{:?}", ranges);
    for range in ranges {
        cnt_inside += range.diff();
    }
    println!("Count everything: {cnt_inside}");
}
