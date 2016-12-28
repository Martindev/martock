#![cfg(test)]

use block;
use world;

#[test]
fn sunny_day() {
    let mut w = world::World::new();

    w.set_block(10, 10, block::Block::Ether);
    assert_eq!(w.block(10, 10), Some(block::Block::Ether));
    assert_eq!(w.block(10, 11), None);
    assert_eq!(w.block(10, 9), None);
}
