use body;
use committer;

pub trait Entity<'a> {
    fn body(&self) -> Option<&'a body::Body>;
    fn committer(&self) -> Option<&'a committer::Committer<'a>>;
}
