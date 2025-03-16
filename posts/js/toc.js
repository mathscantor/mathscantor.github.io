document.addEventListener("DOMContentLoaded", function () {
    console.log("TOC script loaded!"); // Debugging
  
    const headers = document.querySelectorAll("h2, h3, h4, h5, h6");
    const tocLinks = document.querySelectorAll("#sticky-toc a");
  
    if (headers.length === 0 || tocLinks.length === 0) {
      console.warn("No headers or TOC links found. Check if TOC is properly generated.");
      return;
    }
  
    let lastHighlightedHeader = null;
  
    function highlightTOC() {
      let currentHeader = lastHighlightedHeader;  // Start with the last highlighted header
  
      headers.forEach((header, index) => {
        const rect = header.getBoundingClientRect();
        const nextHeader = headers[index + 1];
  
        // Set the buffer zone where the header should be considered near the top
        const bufferZone = 100; // Adjust this value based on your preference (e.g., 100px)
  
        // Check if the current header is near the top of the viewport and still visible
        if (rect.top <= bufferZone && rect.bottom > 0) {
          currentHeader = header.getAttribute("id");
        }
  
        // If the next header is near the top, switch to it
        if (nextHeader) {
          const nextRect = nextHeader.getBoundingClientRect();
          if (nextRect.top <= bufferZone && nextRect.bottom > 0) {
            currentHeader = nextHeader.getAttribute("id");
          }
        }
      });
  
      // If the current header is different from the last highlighted, update it
      if (currentHeader !== lastHighlightedHeader) {
        lastHighlightedHeader = currentHeader;
      }
  
      // Highlight the correct TOC link
      tocLinks.forEach(link => {
        link.classList.remove("active");
        if (lastHighlightedHeader && link.getAttribute("href") === `#${lastHighlightedHeader}`) {
          link.classList.add("active");
        }
      });
    }
  
    window.addEventListener("scroll", highlightTOC);
    highlightTOC(); // Run on page load
  });
  