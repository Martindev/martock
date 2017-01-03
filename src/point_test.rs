#![cfg(test)]

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
