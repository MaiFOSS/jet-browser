use std::fs;
use std::path::Path;
use web_archive::blocking;

fn main() -> std::io::Result<()> {
    let archive = blocking::archive("https://www.google.com", Default::default())
        .expect("Failed to archive the page");
    let page = archive.embed_resources();
    
    let output_dir = Path::new("output");
    fs::create_dir_all(output_dir)?;

    let file_path = output_dir.join("result.html");

    fs::write(&file_path, page)
        .expect("Failed to write the output to file");

    println!("Output saved to {:?}", file_path);
    Ok(())
}
