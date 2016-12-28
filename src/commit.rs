use block;
use tool;

pub struct Commit {
    pub block: block::BlockID,
    pub next_state: block::Block,
    pub tool: tool::Tool,
}
