from abc import ABC, abstractmethod
from typing import TypeVar, List, Optional, Dict

import re


class Product:
    def __init__(self, name: str, price: float) -> None:
        self.name: str = name
        self.price: float = price


class ServerError(Exception):
    pass


class TooManyProductsFoundError(ServerError):
    pass


class Server(ABC):
    n_max_returned_entries: int = 3

    def __init__(self, *args, **kwargs) -> None:
        super().__init__()

    def get_entries(self, n_letters: int = 1) -> List[Product]:
        pattern = '^[a-zA-Z]{{{n_letters}}}\\d{{2,3}}$'.format(n_letters=n_letters)
        entries = [p for p in self._get_all_products(n_letters)
                   if re.match(pattern, p.name)]
        if len(entries) > Server.n_max_returned_entries:
            raise TooManyProductsFoundError
        return sorted(entries, key=lambda entry: entry.price)

    @abstractmethod
    def _get_all_products(self, n_letters: int = 1) -> List[Product]:
        raise NotImplementedError


ServerType = TypeVar('ServerType', bound=Server)


class ListServer(Server):
    def __init__(self, products: List[Product], *args, **kwargs) -> None:
        super().__init__(*args, **kwargs)
        self.products: List[Product] = products

    def _get_all_products(self, n_letters: int = 1) -> List[Product]:
        return self.products


class MapServer(Server):
    def __init__(self, products: List[Product], *args, **kwargs) -> None:
        super().__init__(*args, **kwargs)
        self.products: Dict[str, Product] = {p.name: p.price for p in products}

    def _get_all_products(self, n_letters: int = 1) -> List[Product]:
        return list(self.products.values())


class Client:
    def __init__(self, server: ServerType) -> None:
        self.server: ServerType = server

    def get_total_price(self, n_letters: Optional[int]) -> float:
        try:
            entries = self.server.get_entries() if n_letters is None \
                else self.server.get_entries(n_letters)
            return sum([entry.price for entry in entries])
        except TooManyProductsFoundError:
            return 0


if __name__ == "__main__":
    pass
