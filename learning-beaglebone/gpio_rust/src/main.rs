use gpio_rust::OutputPin;
use std::{process, thread, time};
use simple_signal::Signal;

fn main() {
    let mut output: OutputPin = OutputPin::new(20);
    simple_signal::set_handler(&[Signal::Int, Signal::Term], |signals| {
        println!("Received signal: {:?}\nExiting...", signals);
        process::exit(1);
    });

    let half_sec = time::Duration::from_millis(50000);
    thread::sleep(half_sec);
    thread::sleep(half_sec);
    thread::sleep(half_sec);
    thread::sleep(half_sec);
    /*loop {
        thread::sleep(half_sec);
        output.toggle();
    }*/
}
