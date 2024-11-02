/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_THIRD_PARTY_BLINK_RENDERER_CORE_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_HTML_NODE_DOM_ROOT_H_
#define BRAVE_THIRD_PARTY_BLINK_RENDERER_CORE_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_HTML_NODE_DOM_ROOT_H_

#include "brave/third_party/blink/renderer/core/brave_page_graph/graph_item/node/html/node_html_element.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace brave_page_graph {

/// The DOM root indicates the root node of a document.

/// The DOM root is the child node of a [parser](\ref brave_page_graph::NodeParser) node connected via a [create node](\ref brave_page_graph::EdgeNodeCreate) edge.
/// The node contains the URL the DOM belongs to.
/// Its child node is the HTML element <html> that is connected via the [structure](\ref brave_page_graph::EdgeStructure) edge.
/// It follows HEAD, BODY, and the rest of the document structure as a DOM tree structure connected via [structure](\ref brave_page_graph::EdgeStructure) edges.
/// All such HTML elements are inserted by the [parser](\ref brave_page_graph::NodeParser) node.

/// In the PageGraph, there is at least one DOM root for about:blank and one for the crawled top-level request.

/// This node has a node id attribute. It is used with the [insert node](\ref brave_page_graph::EdgeNodeInsert) edge to represent the structure of the DOM.

class NodeDOMRoot final : public NodeHTMLElement {
 public:
  NodeDOMRoot(GraphItemContext* context,
              const blink::DOMNodeId dom_node_id,
              const String& tag_name,
              bool is_attached);

  void SetURL(const String& url) { url_ = url; }
  const String& GetURL() const { return url_; }

  ItemName GetItemName() const override;
  ItemDesc GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc,
                            xmlNodePtr parent_node) const override;

  bool IsNodeDOMRoot() const override;

 private:
  String url_;
  const bool is_attached_;
};

}  // namespace brave_page_graph

namespace blink {

template <>
struct DowncastTraits<brave_page_graph::NodeDOMRoot> {
  static bool AllowFrom(const brave_page_graph::NodeHTMLElement& element_node) {
    return element_node.IsNodeDOMRoot();
  }
  static bool AllowFrom(const brave_page_graph::NodeHTML& html_node) {
    return IsA<brave_page_graph::NodeDOMRoot>(
        DynamicTo<brave_page_graph::NodeHTMLElement>(html_node));
  }
  static bool AllowFrom(const brave_page_graph::GraphNode& node) {
    return IsA<brave_page_graph::NodeDOMRoot>(
        DynamicTo<brave_page_graph::NodeHTML>(node));
  }
  static bool AllowFrom(const brave_page_graph::GraphItem& graph_item) {
    return IsA<brave_page_graph::NodeDOMRoot>(
        DynamicTo<brave_page_graph::GraphNode>(graph_item));
  }
};

}  // namespace blink

#endif  // BRAVE_THIRD_PARTY_BLINK_RENDERER_CORE_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_HTML_NODE_DOM_ROOT_H_
