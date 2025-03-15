document.addEventListener("DOMContentLoaded", function () {
    const sections = document.querySelectorAll("section[id]"); // Target sections with IDs
    const tocLinks = document.querySelectorAll("#sticky-toc a");

    const observer = new IntersectionObserver(entries => {
        entries.forEach(entry => {
            console.log("hi");
            if (entry.isIntersecting) {
                tocLinks.forEach(link => {
                    link.classList.remove("active");
                    if (link.getAttribute("href").substring(1) === entry.target.id) {
                        link.classList.add("active");
                    }
                });
            }
        });
    }, { threshold: 0.5 }); // 50% of section must be visible

    sections.forEach(section => observer.observe(section));
});
