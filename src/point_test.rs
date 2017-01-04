#![cfg(test)]

use nalgebra;

use world;
use point::Point;

#[test]
fn valid() {
    assert_eq!(Point::from(-109.0, world::FLOOR as f64 - 1.0),
               Point::from(-109.0, world::FLOOR as f64));
    assert_eq!(Point::from(0.0, world::HEIGHT as f64 + 1.0),
               Point::from(0.0, world::HEIGHT as f64));
    assert_ne!(Point::from(0.0, 0.0), Point::from(0.0, 1.0));
    assert_ne!(Point::from(1.0, 0.0), Point::from(0.0, 1.0));
}

#[test]
fn block_resolve() {
    assert_eq!(Point::from(5.0, 0.0).block_pos(), (5, 0));
    assert_eq!(Point::from(-9.5, 9.0).block_pos(), (-10, 9));
}

fn approx_eq(a: (f64, f64), b: (f64, f64)) -> bool {
    nalgebra::approx_eq(&a.0, &b.0) && nalgebra::approx_eq(&a.1, &b.1)
}

#[test]
fn block_offsets() {
    assert!(approx_eq(Point::from(-9.6, 9.0).block_offsets(), (0.4, 0.0)));
    assert!(approx_eq(Point::from(9.6, 9.8).block_offsets(), (0.6, 0.8)));
}
