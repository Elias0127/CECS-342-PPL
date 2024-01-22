use rand::prelude::*;
use std::collections::HashSet;
use std::io::{self, Read, Write};

// Main function to run the program
fn main() {
    let mut rng = thread_rng();
    let mut nums = HashSet::new();
    let mut array = [0; 31];

    // Fill the array with unique random numbers
    while nums.len() < array.len() {
        let num = rng.gen_range(10..100);
        nums.insert(num);
    }

    let mut i = 0;
    for num in nums.iter() {
        array[i] = *num;
        i += 1;
    }

    // Display the tree before sorting
    println!("Unsorted tree:");
    display_tree(&array, 4);
    pause();

    // Perform heap sort and display the array after each move
    println!("Sorting process:");
    heap_sort(&mut array, |a| {
        println!("{:?}", a);
        pause();
    });

    // Display the tree after sorting
    println!("Sorted tree:");
    display_tree(&array, 4);

    // Announce completion and display sorted numbers
    println!("The binary tree is now sorted!");
    print!("Sorted numbers: ");
    for &num in &array {
        print!("{} ", num);
    }
    println!();
    pause();
}

// Display the binary tree in a tree-like format
fn display_tree(array: &[i32], depth: usize) {
    // Total width for the tree
    let width = 4 * 2usize.pow(depth as u32);
    for current_depth in 0..=depth {
        let elements = 2usize.pow(current_depth as u32);
        // Space between nodes at this level
        let space_between = width / elements;
        // Space before the first node
        let first_space = space_between / 2 - 1;

        let mut line = String::new();
        line.push_str(&" ".repeat(first_space));

        for i in 0..elements {
            let index = 2usize.pow(current_depth as u32) - 1 + i;
            if index < array.len() {
                line.push_str(&format!("{:02}", array[index]));
                if i < elements - 1 {
                    line.push_str(&" ".repeat(space_between - 2)); // -2 for the two digits in each node
                }
            }
        }
        println!("{}", line);
    }
}

// Perform heap sort on the array
fn heap_sort(array: &mut [i32], mut display: impl FnMut(&[i32])) {
    let end = array.len();
    // Convert array into a heap
    for start in (0..end / 2).rev() {
        sift_down(array, start, end - 1);
    }

    // Move the root of the heap to the end of the array
    for end in (1..array.len()).rev() {
        array.swap(end, 0);
        sift_down(array, 0, end - 1);
        display(array);
    }
}

// Sift down the heap from the root to the end of the array
fn sift_down(array: &mut [i32], start: usize, end: usize) {
    let mut root = start;

    while 2 * root + 1 <= end {
        let child = 2 * root + 1;
        let mut swap = root;

        if array[swap] < array[child] {
            swap = child;
        }
        if child + 1 <= end && array[swap] < array[child + 1] {
            swap = child + 1;
        }
        if swap == root {
            return;
        } else {
            array.swap(root, swap);
            root = swap;
        }
    }
}
// Helper function to pause the program and wait for user input
fn pause() {
    let mut stdin = io::stdin();
    let mut stdout = io::stdout();

    // Prompt the user to press a key to continue
    println!("Press Enter to continue...");
    let _ = stdout.flush();
    let _ = stdin.read(&mut [0u8]).unwrap();
}
