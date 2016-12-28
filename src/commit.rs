use block;
use tool;
use world;

#[derive(Copy, Clone)]
pub struct Commit {
    pub block: world::BlockID,
    pub next_state: block::Block,
    pub tool: tool::Tool,
}
