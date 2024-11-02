This document describes the general structure of the PageGraph. The PageGraph is a graph stored in the GraphML format representing the DOM Tree of a web page, all its changes JavaScript makes to the DOM and all JavaScript activities that occur. It consists of directed edges and nodes, as explained in the following. Additionally, you can find some tips on how to understand the format.

The advantage of his format over other archiving formats is that it does not simply store the content of a page, but also all activities. That allows it to reproduce behavior from the time the page was visited. For example, a advertising or dynamic server exchanges that are miss-represented in classic formats like WARC or HAR can be reproduced with a PageGraph file.

This document is intended as a first introduction to the PageGraph and might be incomplete. Please verify the information before conducting your own experiments based on the PageGraph.

# Nodes
The graph consists of various nodes which we categorized into the following topics.

The first documentation is added to [NodeDOMRoot](\ref brave_page_graph::NodeDOMRoot).

# Edges
All nodes are connected with directed edges. We use the same categories as for the nodes to categorize the edges.