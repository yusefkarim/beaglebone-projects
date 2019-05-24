use std::{thread, time};
use std::sync::Arc;
use std::sync::atomic::{AtomicBool, Ordering};
use simple_signal::Signal;
// From this module
use gpio_rust::{OutputPin, InputPin};

fn main() {
    let stay_alive = Arc::new(AtomicBool::new(true));
    let set_stay_alive = stay_alive.clone();
    let mut output: OutputPin = OutputPin::new(20);
    let mut input: InputPin = InputPin::new(115);

    simple_signal::set_handler(&[Signal::Int, Signal::Term], move |signals| {
        println!("Received signal: {:?}\nExiting...", signals);
        set_stay_alive.store(false, Ordering::SeqCst);
    });

    let half_sec = time::Duration::from_millis(500);

    let child = thread::spawn(move || {
        println!("Starting child thread, press Ctrl-C to exit");
        while stay_alive.load(Ordering::SeqCst) {
            thread::sleep(half_sec);
            output.toggle();
        }
    });

    println!("Main thread is waiting for input pin to go HIGH");
    input.poll_until_high();
    println!("Input pin went high, joining child and waiting for you to exit.");

    child.join().expect("Could not join child thread");
}
