//! commit is the atomic unit of change to the world state.

use block;
use tool;

#[derive(Copy, Clone)]
pub struct Commit {
    pub x: i64,
    pub y: u8,
    pub next_state: block::Block,
    pub tool: tool::Tool,
}
