use std::collections::BTreeMap;
use std::io;

struct Student{
    name: String,
    middle_score: f32,
    final_score: f32,
}

fn main(){
    let err_read = "read fail";
    let err_stoi = "cant change string to int";
    let mut student_num = String::new();

    println!("student number: ");
    io::stdin().read_line(&mut student_num).expect(err_read);
    let student_num: usize = student_num.trim().parse().expect(err_stoi);

    let mut student_map: BTreeMap<String, Student> = BTreeMap::new();

    for _ in 0..student_num{
        let mut name = String::new();
        let mut middle_score = String::new();
        let mut final_score = String::new();

        println!("name: ");
        io::stdin().read_line(&mut name).expect(err_read);
        let name = name.trim().to_string();

        println!("middle_score: ");
        io::stdin().read_line(&mut middle_score).expect(err_read);
        let middle_score: f32 = middle_score.trim().parse().expect(err_stoi);

        println!("final_score: ");
        io::stdin().read_line(&mut final_score).expect(err_read);
        let final_score: f32 = final_score.trim().parse().expect(err_stoi);

        let student = Student{
            name: name.clone(),
            middle_score,
            final_score,
        };

        student_map.insert(name, student);
    }

    for(name, student) in student_map.iter(){
        println!("name: {}, middle_score: {}, final_score: {}",
    name, student.middle_score, student.final_score);
    }
}