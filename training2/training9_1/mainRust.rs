use std::io;

fn main(){
    let mut m = String::new();
    let mut n = String::new();

    println!("행 수: ");
    io::stdin().read_line(&mut m).expect("입력 읽기 실패");
    let m: usize = m.trim().parse().expect("정수로 변환할 수 없습니다");

    println!("열 수: ");
    io::stdin().read_line(&mut n).expect("입력 읽기 실패");
    let n: usize = n.trim().parse().expect("정수로 변환할 수 없습니다");

    let mut matrix1 = vec![vec![0; n]; m];
    let mut matrix2 = vec![vec![0; n]; m];
    let mut result = vec![vec![0; n]; m];

    println!("첫 번째 행렬의 요소: ");
    for i in 0..m{
        for j in 0..n{
            let mut input = String::new();
            io::stdin().read_line(&mut input).expect("입력 읽기 실패");
            matrix1[i][j] = input.trim().parse().expect("정수로 변환할 수 없습니다");
        }
    }

    println!("두 번째 행렬의 요소: ");
    for i in 0..m{
        for j in 0..n{
            let mut input = String::new();
            io::stdin().read_line(&mut input).expect("입력 읽기 실패");
            matrix2[i][j] = input.trim().parse().expect("정수로 변환할 수 없습니다");
        }
    }

    for i in 0..m {
        for j in 0..n {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    println!("두 행렬의 합:");
    for i in 0..m {
        for j in 0..n {
            print!("{} ", result[i][j]);
        }
        println!();
    }
}
