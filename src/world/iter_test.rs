#![cfg(test)]

use world;
use block::Block;

#[test]
fn block() {
    let mut w = world::World::new();

    // (-1, 0) (0, 0)
    // (-1, 1) (0, 1)

    w.set_block(-1, 0, Block::Ether);
    w.set_block(-1, 1, Block::Ether);
    w.set_block(0, 0, Block::Ether);
    w.set_block(0, 1, Block::Ether);

    let mut iter = w.iter(-1, 0, 2, 2);

    assert_eq!(iter.next(), Some((-1, 0, Some(Block::Ether))));
    assert_eq!(iter.next(), Some((0, 0, Some(Block::Ether))));
    assert_eq!(iter.next(), Some((-1, 1, Some(Block::Ether))));
    assert_eq!(iter.next(), Some((0, 1, Some(Block::Ether))));
    assert_eq!(iter.next(), None);
}
