# Search Discoverability Notes

Google Search Central documents that XML sitemaps should use fully qualified absolute URLs, live at the site root when possible, and list canonical pages the owner wants crawled. A sitemap is a hint rather than a guarantee; it can be submitted in Search Console or referenced from robots.txt. Source: https://developers.google.com/search/docs/crawling-indexing/sitemaps/build-sitemap

Google recommends JSON-LD for structured data and states that markup should describe visible page content, remain accessible to Googlebot, and be tested with the Rich Results Test and URL Inspection. Structured data can help Google understand a page but does not guarantee a rich result or ranking. Sources: https://developers.google.com/search/docs/appearance/structured-data/intro-structured-data and https://developers.google.com/search/docs/appearance/structured-data/sd-policies

For software applications, Google documents `SoftwareApplication` markup with a name and offer price as required for software-app rich-result eligibility, plus recommended application category and operating system. The app page must be publicly crawlable and should be submitted for recrawling through Search Console after deployment. Source: https://developers.google.com/search/docs/appearance/structured-data/software-app

Application to Sexy S-Pen and NCOM AudeX: use distinct canonical GitHub Pages URLs, root-level sitemap.xml and robots.txt files on each Pages site, visible project descriptions that match JSON-LD, accurate `SoftwareApplication` markup, reciprocal repository links, descriptive titles/headings, and GitHub repository topics. Do not use fake ratings, invisible keyword stuffing, or claims that are not visible on the pages.
