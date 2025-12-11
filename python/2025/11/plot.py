import sys

import networkx as nx
from pyvis.network import Network


def plot(graph, highlight=[]):
    # Create NetworkX graph for better layout
    G = nx.DiGraph(graph)

    # Use kamada_kawai layout for better clustering of connected nodes
    try:
        pos = nx.kamada_kawai_layout(G, scale=1000)
    except:
        pos = nx.spring_layout(G, k=3, iterations=100, scale=1000)

    # Create network
    net = Network(
        notebook=True, directed=True, height="750px", width="100%", bgcolor="#ffffff"
    )

    # Calculate degrees
    in_deg = {node: 0 for node in graph}
    out_deg = {node: len(neighbors) for node, neighbors in graph.items()}

    for neighbors in graph.values():
        for n in neighbors:
            in_deg[n] = in_deg.get(n, 0) + 1

    # Add nodes with layout positions
    for node in set(graph.keys()) | set(
        n for neighbors in graph.values() for n in neighbors
    ):
        degree = in_deg.get(node, 0) + out_deg.get(node, 0)
        color = "#ff6b6b" if node in highlight else "#4ecdc4"
        x, y = pos[node][0], pos[node][1]
        net.add_node(
            node,
            label=node,
            size=15 + degree * 8,
            color=color,
            x=x,
            y=y,
            font={"size": 20, "color": "black", "face": "arial", "bold": True},
        )

    # Add edges
    for node, neighbors in graph.items():
        for neighbor in neighbors:
            net.add_edge(node, neighbor)

    # Enable physics with gravity to reveal funnel structures
    net.set_options(
        """
    {
      "physics": {
        "enabled": true,
        "barnesHut": {
          "gravitationalConstant": -15000,
          "centralGravity": 0.5,
          "springLength": 150,
          "springConstant": 0.04,
          "damping": 0.5,
          "avoidOverlap": 0.2
        },
        "stabilization": {
          "enabled": true,
          "iterations": 1000
        }
      }
    }
    """
    )

    net.show("graph.html")


if __name__ == "__main__":
    # nodes piped to sys.stdin
    nodes = {}
    if not sys.stdin.isatty():
        for line in sys.stdin:
            origin = line.strip().split(":")[0]
            dest = line.strip().split(":")[1].strip().split(" ")
            nodes[origin] = dest
    nodes["out"] = []
    plot(nodes, highlight=["dac", "fft", "svr", "out"])
