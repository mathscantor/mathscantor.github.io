(function () {
  var theme =
    document.documentElement.getAttribute("data-theme") === "dark"
      ? "dark"
      : "default";

  mermaid.initialize({
    startOnLoad: true,
    theme: theme,
    securityLevel: "strict",
    fontFamily: "inherit",
  });
})();
