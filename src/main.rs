mod block;
mod body;
mod commit;
mod committer;
mod tool;
mod world;

fn arbite(w: &mut world::World, c: commit::Commit) {}

fn arbiter(w: &mut world::World, cls: &[committer::CL]) {
    for cl in cls {
        for commit in cl.commits() {
            arbite(w, commit);
        }
    }
}

fn reality(w: &world::World, bodies: &mut [&body::Body]) {}

fn engine(mut w: world::World, mut bodies: Vec<&body::Body>, mut committers: Vec<&committer::Committer>) {
    loop {
        let mut cls = Vec::new();
        for c in committers.iter() {
            if let Some(cl) = c.cl(&w, &bodies) {
                cls.push(cl);
            }
        }

        arbiter(&mut w, cls.as_slice());
        reality(&w, bodies.as_mut_slice());

    }
}

fn main() {     
}
