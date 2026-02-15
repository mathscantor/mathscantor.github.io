document.addEventListener("DOMContentLoaded", function () {
    console.log("Caption numbering script loaded!"); // Debugging

    const types = ["figure", "table", "listing", "video"];
    let counters = { figure: 0, table: 0, listing: 0, video: 0 };

    const captions = document.querySelectorAll(".caption");

    captions.forEach(caption => {
        const type = caption.getAttribute("data-type");
        
        if (types.includes(type)) { 
            counters[type]++;
            caption.innerHTML = `${capitalize(type)} ${counters[type]}. ${caption.innerHTML}`;
        }
    });

    function capitalize(word) {
        return word.charAt(0).toUpperCase() + word.slice(1);
    }
});
