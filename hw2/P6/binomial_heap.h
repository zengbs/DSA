static inline void __iheap_union(struct iheap* heap, struct iheap_node* h2)
{
	struct iheap_node* h1;
	struct iheap_node *prev, *x, *next;
	if (!h2)
		return;
	h1 = heap->head;
	if (!h1) {
		heap->head = h2;
		return;
	}
	h1 = __iheap_merge(h1, h2);
	prev = NULL;
	x    = h1;
	next = x->next;
	while (next) {
		if (x->degree != next->degree ||
		    (next->next && next->next->degree == x->degree)) {
			/* nothing to do, advance */
			prev = x;
			x    = next;
		} else if (x->key < next->key) {
			/* x becomes the root of next */
			x->next = next->next;
			__iheap_link(x, next);
		} else {
			/* next becomes the root of x */
			if (prev)
				prev->next = next;
			else
				h1 = next;
			__iheap_link(next, x);
			x = next;
		}
		next = x->next;
	}
	heap->head = h1;
}
